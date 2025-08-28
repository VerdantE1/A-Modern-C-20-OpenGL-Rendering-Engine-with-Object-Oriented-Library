#pragma once
#include "Component.h"
#include "Transform.h"

class TransformComponent : public Component {
public:
    TransformComponent() = default;
    TransformComponent(const glm::vec3& position, const glm::vec3& rotation = glm::vec3(0), const glm::vec3& scale = glm::vec3(1))
        : m_Transform() {
        m_Transform.setPosition(position.x, position.y, position.z);
        m_Transform.setRotation(rotation.x, rotation.y, rotation.z);
        m_Transform.setScale(scale.x, scale.y, scale.z);
    }
    
    // Transform 操作的封装
    void SetPosition(const glm::vec3& position) {
        m_Transform.setPosition(position.x, position.y, position.z);
    }
    
    void SetPosition(float x, float y, float z) {
        m_Transform.setPosition(x, y, z);
    }
    
    void SetRotation(const glm::vec3& rotation) {
        m_Transform.setRotation(rotation.x, rotation.y, rotation.z);
    }
    
    void SetRotation(float pitch, float yaw, float roll) {
        m_Transform.setRotation(pitch, yaw, roll);
    }
    
    void SetScale(const glm::vec3& scale) {
        m_Transform.setScale(scale.x, scale.y, scale.z);
    }
    
    void SetScale(float sx, float sy, float sz) {
        m_Transform.setScale(sx, sy, sz);
    }
    
    // 获取方法
    const glm::vec3& GetPosition() const { return m_Transform.getPosition(); }
    const glm::vec3& GetRotation() const { return m_Transform.getRotation(); }
    const glm::mat4& GetMatrix() const { return m_Transform.getMatrix(); }
    
    // 直接访问Transform（如果需要更复杂的操作）
    Transform& GetTransform() { return m_Transform; }
    const Transform& GetTransform() const { return m_Transform; }

private:
    Transform m_Transform;
};