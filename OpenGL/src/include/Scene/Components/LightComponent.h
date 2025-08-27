#pragma once
#include "Component.h"
#include <glm/glm.hpp>

class LightComponent : public Component {
public:
    enum class LightType {
        DIRECTIONAL,
        POINT,
        SPOT
    };
    
    LightComponent(LightType type = LightType::POINT)
        : m_Type(type) {}
    
    // 光源属性
    glm::vec3 ambient = glm::vec3(0.1f);
    glm::vec3 diffuse = glm::vec3(1.0f);
    glm::vec3 specular = glm::vec3(1.0f);
    
    // 点光源和聚光灯属性
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
    
    // 聚光灯属性
    glm::vec3 direction = glm::vec3(0, -1, 0);
    float cutOff = glm::cos(glm::radians(12.5f));
    float outerCutOff = glm::cos(glm::radians(15.0f));
    
    LightType GetType() const { return m_Type; }
    void SetType(LightType type) { m_Type = type; }

private:
    LightType m_Type;
};