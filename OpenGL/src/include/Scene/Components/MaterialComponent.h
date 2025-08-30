#pragma once
#include "Component.h"
#include <glm/glm.hpp>

class MaterialComponent : public Component {
public:
    //扩展的材质类型枚举
    enum class MaterialType {
        // 贵重金属
        GOLD,
        SILVER,
        BRONZE,
        COPPER,
        PLATINUM,
        
        // 普通金属
        IRON,
        STEEL,
        ALUMINUM,
        BRASS,
        TIN,
        
        // 塑料材质
        PLASTIC_RED,
        PLASTIC_GREEN,
        PLASTIC_BLUE,
        PLASTIC_WHITE,
        PLASTIC_BLACK,
        PLASTIC_YELLOW,
        
        // 橡胶材质
        RUBBER_BLACK,
        RUBBER_RED,
        RUBBER_BLUE,
        
        // 宝石材质
        EMERALD,
        RUBY,
        SAPPHIRE,
        DIAMOND,
        PEARL,
        
        // 木材和石材
        WOOD_OAK,
        WOOD_PINE,
        MARBLE_WHITE,
        MARBLE_BLACK,
        GRANITE,
        CONCRETE,
        
        // 特殊材质
        CHROME,
        OBSIDIAN,
        JADE,
        TURQUOISE,
        
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
        LOG_LEVEL_DEBUG(2, "MaterialComponent: Applied material properties to shader.");
    }

    // 🆕 设置预定义材质（扩展版）
    void SetMaterial(MaterialType type) {
        switch (type) {
            // ========== 贵重金属 ========= =
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
            case MaterialType::COPPER:
                ambient = glm::vec4(0.1913f, 0.0735f, 0.0225f, 1.0f);
                diffuse = glm::vec4(0.7038f, 0.2703f, 0.0828f, 1.0f);
                specular = glm::vec4(0.2566f, 0.1376f, 0.0864f, 1.0f);
                shininess = 12.8f;
                break;
            case MaterialType::PLATINUM:
                ambient = glm::vec4(0.2f, 0.2f, 0.22f, 1.0f);
                diffuse = glm::vec4(0.6f, 0.6f, 0.67f, 1.0f);
                specular = glm::vec4(0.8f, 0.8f, 0.9f, 1.0f);
                shininess = 89.6f;
                break;

            // ========== 普通金属 =========
            case MaterialType::IRON:
                ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
                diffuse = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
                specular = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
                shininess = 30.0f;
                break;
            case MaterialType::STEEL:
                ambient = glm::vec4(0.15f, 0.15f, 0.15f, 1.0f);
                diffuse = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
                specular = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
                shininess = 64.0f;
                break;
            case MaterialType::ALUMINUM:
                ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
                diffuse = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
                specular = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
                shininess = 76.8f;
                break;
            case MaterialType::BRASS:
                ambient = glm::vec4(0.329412f, 0.223529f, 0.027451f, 1.0f);
                diffuse = glm::vec4(0.780392f, 0.568627f, 0.113725f, 1.0f);
                specular = glm::vec4(0.992157f, 0.941176f, 0.807843f, 1.0f);
                shininess = 27.8974f;
                break;
            case MaterialType::TIN:
                ambient = glm::vec4(0.2f, 0.2f, 0.22f, 1.0f);
                diffuse = glm::vec4(0.6f, 0.6f, 0.65f, 1.0f);
                specular = glm::vec4(0.5f, 0.5f, 0.55f, 1.0f);
                shininess = 20.0f;
                break;

            // ========== 塑料材质 =========
            case MaterialType::PLASTIC_RED:
                ambient = glm::vec4(0.1f, 0.02f, 0.02f, 1.0f);
                diffuse = glm::vec4(0.8f, 0.1f, 0.1f, 1.0f);
                specular = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
                shininess = 32.0f;
                break;
            case MaterialType::PLASTIC_GREEN:
                ambient = glm::vec4(0.02f, 0.1f, 0.02f, 1.0f);
                diffuse = glm::vec4(0.1f, 0.8f, 0.1f, 1.0f);
                specular = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
                shininess = 32.0f;
                break;
            case MaterialType::PLASTIC_BLUE:
                ambient = glm::vec4(0.02f, 0.02f, 0.1f, 1.0f);
                diffuse = glm::vec4(0.1f, 0.1f, 0.8f, 1.0f);
                specular = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
                shininess = 32.0f;
                break;
            case MaterialType::PLASTIC_WHITE:
                ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
                diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
                specular = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
                shininess = 32.0f;
                break;
            case MaterialType::PLASTIC_BLACK:
                ambient = glm::vec4(0.02f, 0.02f, 0.02f, 1.0f);
                diffuse = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
                specular = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
                shininess = 32.0f;
                break;
            case MaterialType::PLASTIC_YELLOW:
                ambient = glm::vec4(0.1f, 0.1f, 0.02f, 1.0f);
                diffuse = glm::vec4(0.8f, 0.8f, 0.1f, 1.0f);
                specular = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
                shininess = 32.0f;
                break;

            // ========== 橡胶材质 =========
            case MaterialType::RUBBER_BLACK:
                ambient = glm::vec4(0.02f, 0.02f, 0.02f, 1.0f);
                diffuse = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
                specular = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
                shininess = 10.0f;
                break;
            case MaterialType::RUBBER_RED:
                ambient = glm::vec4(0.05f, 0.01f, 0.01f, 1.0f);
                diffuse = glm::vec4(0.5f, 0.05f, 0.05f, 1.0f);
                specular = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
                shininess = 10.0f;
                break;
            case MaterialType::RUBBER_BLUE:
                ambient = glm::vec4(0.01f, 0.01f, 0.05f, 1.0f);
                diffuse = glm::vec4(0.05f, 0.05f, 0.5f, 1.0f);
                specular = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
                shininess = 10.0f;
                break;

            // ========== 宝石材质 =========
            case MaterialType::EMERALD:
                ambient = glm::vec4(0.0215f, 0.1745f, 0.0215f, 1.0f);
                diffuse = glm::vec4(0.07568f, 0.61424f, 0.07568f, 1.0f);
                specular = glm::vec4(0.633f, 0.727811f, 0.633f, 1.0f);
                shininess = 76.8f;
                break;
            case MaterialType::RUBY:
                ambient = glm::vec4(0.1745f, 0.01175f, 0.01175f, 1.0f);
                diffuse = glm::vec4(0.61424f, 0.04136f, 0.04136f, 1.0f);
                specular = glm::vec4(0.727811f, 0.626959f, 0.626959f, 1.0f);
                shininess = 76.8f;
                break;
            case MaterialType::SAPPHIRE:
                ambient = glm::vec4(0.01175f, 0.01175f, 0.1745f, 1.0f);
                diffuse = glm::vec4(0.04136f, 0.04136f, 0.61424f, 1.0f);
                specular = glm::vec4(0.626959f, 0.626959f, 0.727811f, 1.0f);
                shininess = 76.8f;
                break;
            case MaterialType::DIAMOND:
                ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
                diffuse = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
                specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
                shininess = 128.0f;
                break;
            case MaterialType::PEARL:
                ambient = glm::vec4(0.25f, 0.20725f, 0.20725f, 1.0f);
                diffuse = glm::vec4(1.0f, 0.829f, 0.829f, 1.0f);
                specular = glm::vec4(0.296648f, 0.296648f, 0.296648f, 1.0f);
                shininess = 11.264f;
                break;

            // ========== 木材和石材 =========
            case MaterialType::WOOD_OAK:
                ambient = glm::vec4(0.1f, 0.05f, 0.02f, 1.0f);
                diffuse = glm::vec4(0.6f, 0.3f, 0.1f, 1.0f);
                specular = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
                shininess = 5.0f;
                break;
            case MaterialType::WOOD_PINE:
                ambient = glm::vec4(0.08f, 0.06f, 0.03f, 1.0f);
                diffuse = glm::vec4(0.5f, 0.4f, 0.2f, 1.0f);
                specular = glm::vec4(0.15f, 0.15f, 0.15f, 1.0f);
                shininess = 3.0f;
                break;
            case MaterialType::MARBLE_WHITE:
                ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
                diffuse = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
                specular = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
                shininess = 89.6f;
                break;
            case MaterialType::MARBLE_BLACK:
                ambient = glm::vec4(0.05f, 0.05f, 0.05f, 1.0f);
                diffuse = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
                specular = glm::vec4(0.6f, 0.6f, 0.6f, 1.0f);
                shininess = 89.6f;
                break;
            case MaterialType::GRANITE:
                ambient = glm::vec4(0.1f, 0.1f, 0.12f, 1.0f);
                diffuse = glm::vec4(0.4f, 0.4f, 0.45f, 1.0f);
                specular = glm::vec4(0.5f, 0.5f, 0.55f, 1.0f);
                shininess = 45.0f;
                break;
            case MaterialType::CONCRETE:
                ambient = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
                diffuse = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
                specular = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
                shininess = 1.0f;
                break;

            // ========== 特殊材质 =========
            case MaterialType::CHROME:
                ambient = glm::vec4(0.25f, 0.25f, 0.25f, 1.0f);
                diffuse = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
                specular = glm::vec4(0.774597f, 0.774597f, 0.774597f, 1.0f);
                shininess = 76.8f;
                break;
            case MaterialType::OBSIDIAN:
                ambient = glm::vec4(0.05375f, 0.05f, 0.06625f, 1.0f);
                diffuse = glm::vec4(0.18275f, 0.17f, 0.22525f, 1.0f);
                specular = glm::vec4(0.332741f, 0.328634f, 0.346435f, 1.0f);
                shininess = 38.4f;
                break;
            case MaterialType::JADE:
                ambient = glm::vec4(0.135f, 0.2225f, 0.1575f, 1.0f);
                diffuse = glm::vec4(0.54f, 0.89f, 0.63f, 1.0f);
                specular = glm::vec4(0.316228f, 0.316228f, 0.316228f, 1.0f);
                shininess = 12.8f;
                break;
            case MaterialType::TURQUOISE:
                ambient = glm::vec4(0.1f, 0.18725f, 0.1745f, 1.0f);
                diffuse = glm::vec4(0.396f, 0.74151f, 0.69102f, 1.0f);
                specular = glm::vec4(0.297254f, 0.30829f, 0.306678f, 1.0f);
                shininess = 12.8f;
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