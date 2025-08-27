#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include <glm/glm.hpp>
#include "Entity.h" 

class RotationAnimation : public Component {
public:
    RotationAnimation(float speed = 1.0f, const glm::vec3& axis = glm::vec3(0, 1, 0))
        : m_Speed(speed), m_Axis(axis) {}
    
    void Update(float deltaTime) override {
        if (!GetOwner()) return;
        
        auto transform = GetOwner()->GetTransform();

        if (!transform) return;
        
        // 累积旋转角度
        m_CurrentRotation += m_Speed * deltaTime;
        
        // 应用旋转（这里简化为绕单轴旋转）
        glm::vec3 rotation = transform->GetRotation();
        rotation.x = m_Axis.x * m_CurrentRotation;
        rotation.y = m_Axis.y * m_CurrentRotation;
        rotation.z = m_Axis.z * m_CurrentRotation;
        
        transform->SetRotation(rotation);
    }
    
    void SetSpeed(float speed) { m_Speed = speed; }
    void SetAxis(const glm::vec3& axis) { m_Axis = axis; }
    
    float GetSpeed() const { return m_Speed; }
    const glm::vec3& GetAxis() const { return m_Axis; }

private:
    float m_Speed = 1.0f;
    glm::vec3 m_Axis = glm::vec3(0, 1, 0);
    float m_CurrentRotation = 0.0f;
};