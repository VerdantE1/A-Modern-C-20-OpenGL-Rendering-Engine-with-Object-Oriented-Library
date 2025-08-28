#pragma once
#include "Component.h"
#include "Shader.h"
#include <glm/glm.hpp>

class LightComponent : public Component {
public:
    enum class LightType { DIRECTIONAL, POINT, SPOT };

    LightComponent(LightType type = LightType::POINT)
        : m_Type(type) {
    }

	// 光源属性;位置由Transform组件提供
    glm::vec4 ambient = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    float intensity = 1.0f;           // 可选，整体亮度
    bool enabled = true;               // 光源开关


    // 衰减系数（点光源和聚光灯）
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    // 聚光灯方向和角度
    glm::vec3 direction = glm::vec3(0, -1, 0);
    float cutOff = glm::cos(glm::radians(12.5f));
    float outerCutOff = glm::cos(glm::radians(15.0f));

    LightType GetLightType() const { return m_Type; }
    void SetLightType(LightType type) { m_Type = type; }


	void SetAmbient(const glm::vec4& color) { ambient = color; }
	void SetDiffuse(const glm::vec4& color) { diffuse = color; }
	void SetSpecular(const glm::vec4& color) { specular = color; }
	void SetIntensity(float inten) { intensity = inten; }

    void ApplyToShader(Shader& shader) override {
        if (!enabled) return;
        
        // 获取光源位置（从 Transform 组件）
        if (auto transform = GetOwner()->GetTransform()) {
            glm::vec3 position = transform->GetPosition();
            shader.SetUniform3f("light.position", position.x, position.y, position.z);
        }
        
        shader.SetUniform4f("light.ambient", 
            ambient.r * intensity, ambient.g * intensity, ambient.b * intensity, ambient.a);
        shader.SetUniform4f("light.diffuse", 
            diffuse.r * intensity, diffuse.g * intensity, diffuse.b * intensity, diffuse.a);
        shader.SetUniform4f("light.specular", 
            specular.r * intensity, specular.g * intensity, specular.b * intensity, specular.a);
    }

private:
    LightType m_Type;
};