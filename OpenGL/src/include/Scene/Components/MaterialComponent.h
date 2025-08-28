#pragma once
#include "Component.h"
#include <glm/glm.hpp>

class MaterialComponent : public Component {
public:
    // 材质类型枚举
    enum class MaterialType {
        GOLD,
        SILVER,
        BRONZE,
        CUSTOM
    };

    // 构造函数，默认为金材质
    MaterialComponent() {
        SetMaterial(MaterialType::GOLD);
    }
    
    MaterialComponent(MaterialType type) {
        SetMaterial(type);
    }
    
    // 自定义材质构造函数
    MaterialComponent(const glm::vec4& amb, const glm::vec4& diff, const glm::vec4& spec, float shin)
        : ambient(amb), diffuse(diff), specular(spec), shininess(shin) {}


    // 材质属性
    glm::vec4 ambient = glm::vec4(0.2473f, 0.1995f, 0.0745f, 1.0f);   // 环境光
    glm::vec4 diffuse = glm::vec4(0.7516f, 0.6065f, 0.2265f, 1.0f);   // 漫反射
    glm::vec4 specular = glm::vec4(0.6283f, 0.5559f, 0.3661f, 1.0f);  // 镜面反射
    float shininess = 51.2f;       
    
    // 高光系数
    void ApplyToShader(Shader& shader) override {
        shader.SetUniform4f("material.ambient",
            ambient.r, ambient.g, ambient.b, ambient.a);
        shader.SetUniform4f("material.diffuse",
            diffuse.r, diffuse.g, diffuse.b, diffuse.a);
        shader.SetUniform4f("material.specular",
            specular.r, specular.g, specular.b, specular.a);
        shader.SetUniform1f("material.shininess", shininess);
    }

    // 设置预定义材质
    void SetMaterial(MaterialType type) {
        switch (type) {
            case MaterialType::GOLD:
                ambient = glm::vec4(0.2473f, 0.1995f, 0.0745f, 1.0f);
                diffuse = glm::vec4(0.7516f, 0.6065f, 0.2265f, 1.0f);
                specular = glm::vec4(0.6283f, 0.5559f, 0.3661f, 1.0f);
                shininess = 51.2f;
                break;
            case MaterialType::SILVER:
                ambient = glm::vec4(0.1923f, 0.1923f, 0.1923f, 1.0f);
                diffuse = glm::vec4(0.5075f, 0.5075f, 0.5075f, 1.0f);
                specular = glm::vec4(0.5083f, 0.5083f, 0.5083f, 1.0f);
                shininess = 51.2f;
                break;
            case MaterialType::BRONZE:
                ambient = glm::vec4(0.2125f, 0.1275f, 0.0540f, 1.0f);
                diffuse = glm::vec4(0.7140f, 0.4284f, 0.1814f, 1.0f);
                specular = glm::vec4(0.3936f, 0.2719f, 0.1667f, 1.0f);
                shininess = 25.6f;
                break;
            case MaterialType::CUSTOM:
                // 保持当前值不变
                break;
        }
        m_MaterialType = type;
    }
    
    // 设置材质属性的便捷方法
    void SetAmbient(const glm::vec4& amb) { ambient = amb; m_MaterialType = MaterialType::CUSTOM; }
    void SetDiffuse(const glm::vec4& diff) { diffuse = diff; m_MaterialType = MaterialType::CUSTOM; }
    void SetSpecular(const glm::vec4& spec) { specular = spec; m_MaterialType = MaterialType::CUSTOM; }
    void SetShininess(float shin) { shininess = shin; m_MaterialType = MaterialType::CUSTOM; }
    
    // 设置完整材质
    void SetMaterial(const glm::vec4& amb, const glm::vec4& diff, const glm::vec4& spec, float shin) {
        ambient = amb;
        diffuse = diff;
        specular = spec;
        shininess = shin;
        m_MaterialType = MaterialType::CUSTOM;
    }
    
    MaterialType GetMaterialType() const { return m_MaterialType; }

private:
    MaterialType m_MaterialType = MaterialType::GOLD;
};