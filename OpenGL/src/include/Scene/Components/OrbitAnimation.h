#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include <glm/glm.hpp>

class OrbitAnimation : public Component {
public:
    OrbitAnimation(float radius = 2.0f, float speed = 1.0f, const glm::vec3& center = glm::vec3(0))
        : m_Radius(radius), m_Speed(speed), m_Center(center) {}
    
    void Update(float deltaTime) override {
        if (!GetOwner()) {
			LOG_ERROR("OrbitAnimation: Owner entity is null.");
            return;
        }
        
        auto transform = GetOwner()->GetTransform();
        if (!transform) {
			LOG_ERROR("OrbitAnimation: Transform component is missing.");
            return;
        }
        
        m_CurrentAngle += m_Speed * deltaTime;
        
        // 计算圆周运动位置
        float x = m_Center.x + cos(m_CurrentAngle) * m_Radius;
        float z = m_Center.z + sin(m_CurrentAngle) * m_Radius;
        float y = m_Center.y + sin(m_CurrentAngle * 0.5f) * (m_Radius * 0.3f); // 稍微有点垂直变化
        
        transform->SetPosition(x, y, z);
    }
    
    void SetRadius(float radius) { m_Radius = radius; }
    void SetSpeed(float speed) { m_Speed = speed; }
    void SetCenter(const glm::vec3& center) { m_Center = center; }

private:
    float m_Radius = 2.0f;
    float m_Speed = 1.0f;
    glm::vec3 m_Center = glm::vec3(0);
    float m_CurrentAngle = 0.0f;
};