#pragma once
#include <memory>
#include <vector>
#include <typeindex>
#include <unordered_map>
#include "Component.h"
#include <TransformComponent.h>

class Entity {
public:
    Entity(const std::string& name = "") : m_Name(name) {
        // Transform 是必需组件
        AddComponent<TransformComponent>();
    }
    
	// 添加组件，支持传递构造参数
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
        
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = component.get();
        component->m_Owner = this;
        
        m_Components[std::type_index(typeid(T))] = std::move(component);
        return ptr;
    }
    
    // 获取某个类型的组件（如果有就返回指针，否则返回 nullptr）
    template<typename T>
    T* GetComponent() {
        auto it = m_Components.find(std::type_index(typeid(T)));
        if (it != m_Components.end()) {
            return static_cast<T*>(it->second.get());
        }
        return nullptr;
    }

    //获取 Transform（因为每个实体都必须有）
    TransformComponent* GetTransform() { 
        return GetComponent<TransformComponent>(); 
    }
    
    const std::string& GetName() const { return m_Name; }

private:
    std::string m_Name;
    std::unordered_map<std::type_index, std::unique_ptr<Component>> m_Components;
};