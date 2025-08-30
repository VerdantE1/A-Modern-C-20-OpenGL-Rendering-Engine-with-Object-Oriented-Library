#pragma once
#include "Component.h"
#include "Shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>

// 前向声明
class LightComponent;
class Renderer;
class Entity;

class ShadowComponent : public Component {
public:
    enum class ShadowType {
        NONE,           // 无阴影
        SHADOW_MAP      // 标准阴影映射 (支持所有光源类型)
    };

    enum class Quality {
        LOW,
        MEDIUM,
        HIGH,
        Ultra
    };

    ShadowComponent(ShadowType type = ShadowType::SHADOW_MAP);
    ~ShadowComponent();

    // 阴影映射配置
    void SetShadowMapSize(int width, int height);
    void SetShadowMapQuality(Quality quality);
    void SetShadowType(ShadowType type) { m_shadowType = type; }
    void SetBias(float bias) { m_shadowBias = bias; }
    void SetEnabled(bool enabled) { m_enabled = enabled; }
    bool IsEnabled() const { return m_enabled && m_shadowType != ShadowType::NONE; }
    
    // 获取阴影相关资源
    GLuint GetShadowMapTexture() const { return m_shadowMapTexture; }
    GLuint GetShadowFramebuffer() const { return m_shadowFramebuffer; }
    glm::mat4 GetLightSpaceMatrix() const { return m_lightSpaceMatrix; }
    
    // 渲染流程
    void BeginShadowPass();
    void EndShadowPass();

    
    // 组件生命周期
    void Update(float deltaTime) override;

    // 渲染物体
    void RenderShadowCasters(const Renderer& renderer, const std::vector<std::unique_ptr<Entity>>& entities);

    // 阴影Shader
    std::shared_ptr<Shader> GetShadowShader();

private:
    void InitializeShadowMap();
    void CalculateLightSpaceMatrix();
    std::shared_ptr<Shader> CreateShadowShader();
    
    // 获取关联的光源组件
    LightComponent* GetAssociatedLight() const;
    
    ShadowType m_shadowType = ShadowType::SHADOW_MAP;
    bool m_enabled = true;
    
    // 阴影映射资源
    GLuint m_shadowFramebuffer = 0;
    GLuint m_shadowMapTexture = 0;
    int m_shadowMapWidth = 1024;
    int m_shadowMapHeight = 1024;
    
    // 阴影参数
    float m_shadowBias = 0.005f;
    float m_nearPlane = 1.0f;
    float m_farPlane = 25.0f;
    
    // 光源空间变换矩阵
    glm::mat4 m_lightSpaceMatrix = glm::mat4(1.0f);

        // 阴影着色器
    std::shared_ptr<Shader> m_shadowShader;
};