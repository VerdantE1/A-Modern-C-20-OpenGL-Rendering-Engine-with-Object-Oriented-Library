#include "ShadowComponent.h"
#include "Logger.h"
#include "LightComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Globals.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include <glm/gtc/matrix_transform.hpp>

// ============================= 构造函数和析构函数 =============================

ShadowComponent::ShadowComponent(ShadowType type)
    : m_shadowType(type) {
    LOG_INFO("ShadowComponent: Creating shadow component with type {}",
        type == ShadowType::SHADOW_MAP ? "SHADOW_MAP" : "NONE");

    if (type == ShadowType::SHADOW_MAP) {
        InitializeShadowMap();
    }
}

ShadowComponent::~ShadowComponent() {
    LOG_INFO("ShadowComponent: Destroying shadow component");

    // 清理 OpenGL 资源
    if (m_shadowFramebuffer != 0) {
        GLCall(glDeleteFramebuffers(1, &m_shadowFramebuffer));
        LOG_DEBUG("ShadowComponent: Deleted framebuffer {}", m_shadowFramebuffer);
    }
    if (m_shadowMapTexture != 0) {
        GLCall(glDeleteTextures(1, &m_shadowMapTexture));
        LOG_DEBUG("ShadowComponent: Deleted shadow map texture {}", m_shadowMapTexture);
    }
}

// ============================= 配置方法 =============================

void ShadowComponent::SetShadowMapSize(int width, int height) {
    m_shadowMapWidth = width;
    m_shadowMapHeight = height;
    
    // 如果已经初始化过，需要重新创建
    if (m_shadowFramebuffer != 0) {
        // 清理旧资源
        glDeleteFramebuffers(1, &m_shadowFramebuffer);
        glDeleteTextures(1, &m_shadowMapTexture);

        // 重新初始化
        InitializeShadowMap();
    }
}

void ShadowComponent::SetShadowMapQuality(Quality quality) {
    switch (quality) {
        case Quality::LOW:
            SetShadowMapSize(512, 512);
            break;
        case Quality::MEDIUM:
            SetShadowMapSize(1024, 1024);
            break;
        case Quality::HIGH:
            SetShadowMapSize(2048, 2048);
            break;
        case Quality::Ultra:
            SetShadowMapSize(4096, 4096);
            break;
    }
}

// ============================= 渲染流程方法 =============================

void ShadowComponent::BeginShadowPass() {
    if (!IsEnabled()) {
        LOG_WARNING("ShadowComponent: Shadow pass called but component is disabled");
        return;
    }

    LOG_DEBUG("ShadowComponent: Beginning shadow pass");

    // Step1:切换到阴影帧缓冲区
    glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFramebuffer);

    // Step2: 设置阴影贴图的视口
    glViewport(0, 0, m_shadowMapWidth, m_shadowMapHeight);

    // Step3: 清空深度缓冲区（准备记录新的深度信息）
    glClear(GL_DEPTH_BUFFER_BIT);

    // Step4: 禁用颜色写入，只写入深度
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

    LOG_TRACE("ShadowComponent: Shadow framebuffer {} bound, viewport set to {}x{}",
        m_shadowFramebuffer, m_shadowMapWidth, m_shadowMapHeight);
}

void ShadowComponent::EndShadowPass() {
    if (!IsEnabled()) return;

    LOG_DEBUG("ShadowComponent: Ending shadow pass");

    // Step1: 恢复颜色写入
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

    // Step2: 切换回默认帧缓冲区（屏幕）
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Step3: 恢复主视口尺寸
    glViewport(0, 0, g_WindowWidth, g_WindowHeight);

    LOG_TRACE("ShadowComponent: Switched back to default framebuffer, viewport restored to {}x{}",
        g_WindowWidth, g_WindowHeight);
}

// ============================= 生命周期方法 =============================

void ShadowComponent::Update(float deltaTime) {
    if (!IsEnabled()) return;

    // 每帧重新计算光源空间矩阵（因为光源可能在移动）
    CalculateLightSpaceMatrix();
	LOG_INFO("ShadowComponent: Updated light space matrix");
}

void ShadowComponent::RenderShadowCasters(const Renderer& renderer, const std::vector<std::unique_ptr<Entity>>& entities) {
    if (!IsEnabled()) return;

    auto shadowShader = GetShadowShader();
    if (!shadowShader) {
        LOG_ERROR("ShadowComponent: No shadow shader available");
        return;
    }

    glm::mat4 lightSpaceMatrix = GetLightSpaceMatrix();

    // ShadowComponent 自己渲染所有实体
    for (const auto& entity : entities) {
        auto renderComp = entity->GetComponent<RenderComponent>();
        auto transform = entity->GetTransform();

        if (!renderComp || !transform) continue;
        auto geometry = renderComp->GetGeometry();
        if (!geometry) continue;

        // 使用 ShadowComponent 自己的着色器
		
        shadowShader->Bind();
        shadowShader->SetUniformMat4fv("lightSpaceMatrix", lightSpaceMatrix);
        shadowShader->SetUniformMat4fv("model", transform->GetMatrix());

        
        renderer.Draw(*geometry, *shadowShader);
		LOG_INFO("ShadowComponent: Rendered shadow caster '{}'", entity->GetName());
    }
}

// ============================= 私有辅助方法 =============================

void ShadowComponent::InitializeShadowMap() {
    LOG_INFO("ShadowComponent: Initializing shadow map resources ({}x{})",
        m_shadowMapWidth, m_shadowMapHeight);

    // Step1: 创建帧缓冲区对象
    GLCall(glGenFramebuffers(1, &m_shadowFramebuffer));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_shadowFramebuffer));

    // Step2: 创建深度纹理（用于存储阴影贴图）
    GLCall(glGenTextures(1, &m_shadowMapTexture));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_shadowMapTexture));

    // Step3: 配置深度纹理参数
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
        m_shadowMapWidth, m_shadowMapHeight, 0,
        GL_DEPTH_COMPONENT, GL_FLOAT, NULL));

    // Step4: 设置纹理过滤参数
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    // Step5: 设置纹理包装模式（防止边界采样问题）
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));

    // Step6: 设置边界颜色为白色（边界外认为没有阴影）
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor));

    // Step7: 将深度纹理附加到帧缓冲区的深度附件上
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
        GL_TEXTURE_2D, m_shadowMapTexture, 0));

    // Step8: 禁用颜色缓冲区（只需要深度信息）
    GLCall(glDrawBuffer(GL_NONE));
    GLCall(glReadBuffer(GL_NONE));

    // Step9: 检查帧缓冲区完整性
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG_ERROR("ShadowComponent: Shadow framebuffer is not complete!");
    }

    // Step10: 切换回默认帧缓冲区
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

    LOG_INFO("ShadowComponent: Shadow map initialized - FB:{}, Texture:{}",
        m_shadowFramebuffer, m_shadowMapTexture);
}

LightComponent* ShadowComponent::GetAssociatedLight() const
{
    auto owner = GetOwner();
    if (!owner) {
        LOG_ERROR("ShadowComponent: No owner entity found");
        return nullptr;
    }
    // 假设光源组件和阴影组件在同一个实体上
    auto lightComp = owner->GetComponent<LightComponent>();
    if (!lightComp) {
        LOG_ERROR("ShadowComponent: No associated LightComponent found on entity '{}'", owner->GetName());
        return nullptr;
    }
    return lightComp;
}

void ShadowComponent::CalculateLightSpaceMatrix() {
    auto lightComp = GetAssociatedLight();
    auto transform = GetOwner()->GetTransform();

    if (!lightComp || !transform) {
        LOG_ERROR("ShadowComponent: Cannot calculate light space matrix - missing light or transform");
        return;
    }

    // 步骤1: 获取光源位置
    glm::vec3 lightPos = transform->GetPosition();
    LOG_TRACE("ShadowComponent: Light position: ({}, {}, {})", lightPos.x, lightPos.y, lightPos.z);

    // 步骤2: 根据光源类型计算投影矩阵和视图矩阵
    glm::mat4 lightProjection;
    glm::mat4 lightView;

    switch (lightComp->GetLightType()) {
    case LightComponent::LightType::DIRECTIONAL: {
        // 方向光: 使用正交投影
        float orthoSize = 10.0f;
        lightProjection = glm::ortho(-orthoSize, orthoSize, -orthoSize, orthoSize,
            m_nearPlane, m_farPlane);

        // 方向光从无限远处照射，位置是方向的反向
        glm::vec3 lightTarget = glm::vec3(0.0f);  // 照射目标
        glm::vec3 lightDirection = glm::normalize(lightComp->direction);
        glm::vec3 lightPosition = lightTarget - lightDirection * 10.0f;  // 远处位置

        lightView = glm::lookAt(lightPosition, lightTarget, glm::vec3(0.0f, 1.0f, 0.0f));
        LOG_TRACE("ShadowComponent: Directional light - ortho projection");
        break;
    }
    case LightComponent::LightType::POINT: {
        // 点光源: 使用透视投影
        lightProjection = glm::perspective(glm::radians(90.0f), 1.0f, m_nearPlane, m_farPlane);

        // 从光源位置看向场景中心
        glm::vec3 lightTarget = glm::vec3(0.0f, 0.0f, 0.0f);  // 场景中心
        glm::vec3 lightDirection = glm::normalize(lightTarget - lightPos);

        lightView = glm::lookAt(
            lightPos,                           // 光源位置（摄像机位置）
            lightTarget,                        // 看向的目标点
            glm::vec3(0.0f, 1.0f, 0.0f)        // 上方向向量
        );

        LOG_TRACE("ShadowComponent: Point light - perspective projection, FOV=90°");
        LOG_TRACE("ShadowComponent: Point light looking from ({}, {}, {}) to ({}, {}, {})",
            lightPos.x, lightPos.y, lightPos.z,
            lightTarget.x, lightTarget.y, lightTarget.z);
        break;
    }
    case LightComponent::LightType::SPOT: {
        // 聚光灯: 使用透视投影
        float spotAngle = glm::acos(lightComp->cutOff) * 2.0f;  // 从cutOff计算全角度
        float spotAngleDegrees = glm::degrees(spotAngle);

        // 确保角度在合理范围内
        if (spotAngleDegrees < 10.0f) spotAngleDegrees = 10.0f;
        if (spotAngleDegrees > 120.0f) spotAngleDegrees = 120.0f;

        lightProjection = glm::perspective(glm::radians(spotAngleDegrees), 1.0f, m_nearPlane, m_farPlane);

        // 聚光灯从光源位置沿着指定方向照射
        glm::vec3 lightDirection = glm::normalize(lightComp->direction);
        glm::vec3 lightTarget = lightPos + lightDirection * 5.0f;  // 沿方向延伸一段距离作为目标点

        lightView = glm::lookAt(
            lightPos,                           // 光源位置
            lightTarget,                        // 沿光线方向的目标点
            glm::vec3(0.0f, 1.0f, 0.0f)        // 上方向向量
        );

        LOG_TRACE("ShadowComponent: Spot light - perspective projection, FOV={:.1f}°", spotAngleDegrees);
        LOG_TRACE("ShadowComponent: Spot light direction: ({}, {}, {})",
            lightDirection.x, lightDirection.y, lightDirection.z);
        break;
    }
    default: {
        LOG_ERROR("ShadowComponent: Unknown light type, using default perspective projection");
        lightProjection = glm::perspective(glm::radians(45.0f), 1.0f, m_nearPlane, m_farPlane);
        lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        break;
    }
    }
    
    // 重点：计算最终的光源空间矩阵
    m_lightSpaceMatrix = lightProjection * lightView;
    LOG_TRACE("ShadowComponent: Light space matrix calculated for {} light",
        lightComp->GetLightType() == LightComponent::LightType::DIRECTIONAL ? "directional" :
        lightComp->GetLightType() == LightComponent::LightType::POINT ? "point" : "spot");
}

std::shared_ptr<Shader> ShadowComponent::GetShadowShader() {
    if (!m_shadowShader) {
        m_shadowShader = CreateShadowShader();
    }
    return m_shadowShader;
}

std::shared_ptr<Shader> ShadowComponent::CreateShadowShader() {
    try {
        auto shader = std::make_shared<Shader>("res/shaders/ShadowShader/ShadowPass.shader");
        LOG_INFO("ShadowComponent: Shadow shader created successfully");
        return shader;
    }
    catch (const std::exception& e) {
        LOG_ERROR("ShadowComponent: Failed to create shadow shader: {}", e.what());
        return nullptr;
    }
}