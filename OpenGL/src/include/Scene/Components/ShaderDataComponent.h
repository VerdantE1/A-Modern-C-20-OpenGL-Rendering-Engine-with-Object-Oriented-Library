#pragma once
#include "Component.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <unordered_map>
#include <string>
#include <variant>

//Uniform数据类型
using UniformValue = std::variant<int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4>;
using UniformMap = std::unordered_map<std::string, UniformValue>;

class ShaderDataComponent : public Component {
public:
	ShaderDataComponent() = default;

    // 设置不同类型的 uniform 数据（只存储，不绑定）
    void SetUniform(const std::string& name, int value) {
        m_UniformData[name] = value;
    }

    void SetUniform(const std::string& name, float value) {
        m_UniformData[name] = value;
    }

    void SetUniform(const std::string& name, const glm::vec3& value) {
        m_UniformData[name] = value;
    }

    void SetUniform(const std::string& name, const glm::vec4& value) {
        m_UniformData[name] = value;
    }

    void SetUniform(const std::string& name, const glm::mat4& value) {
        m_UniformData[name] = value;
    }

    // 批量应用所有 uniform 到指定 shader（延迟绑定的关键）
    void ApplyToShader(Shader& shader) const {
        for (const auto& [name, value] : m_UniformData) {
            std::visit([&shader, &name](const auto& val) {
                using T = std::decay_t<decltype(val)>;
                if constexpr (std::is_same_v<T, int>) {
                    shader.SetUniform1i(name, val);
                }
                else if constexpr (std::is_same_v<T, float>) {
                    shader.SetUniform1f(name, val);
                }
                else if constexpr (std::is_same_v<T, glm::vec3>) {
                    shader.SetUniform3f(name, val.x, val.y, val.z);
                }
                else if constexpr (std::is_same_v<T, glm::vec4>) {
                    shader.SetUniform4f(name, val.x, val.y, val.z, val.w);
                }
                else if constexpr (std::is_same_v<T, glm::mat4>) {
                    shader.SetUniformMat4fv(name, val);
                }
                }, value);
        }
    }

    // 获取存储的数据（用于调试或特殊需求）
    const std::unordered_map<std::string, UniformValue>& GetUniformData() const {
        return m_UniformData;
    }

    void Clear() { m_UniformData.clear(); }
   
private:
	UniformMap m_UniformData;

};