#pragma once
#include "Component.h"
#include "Shaper.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "MaterialComponent.h"
#include "ShaderDataComponent.h"
#include <memory>
#include <iostream>

class RenderComponent : public Component {
public:
    RenderComponent() = default;
    
    RenderComponent(std::shared_ptr<Shaper> geometry, 
                   std::shared_ptr<Shader> shader,
                   std::shared_ptr<Texture> texture = nullptr)
        : m_Geometry(geometry), m_Shader(shader), m_Texture(texture) {}

    void Render(const Renderer& renderer, 
               const glm::mat4& projectionMatrix, 
               const glm::mat4& viewMatrix, 
               const glm::mat4& modelMatrix) {
        if (!m_Geometry || !m_Shader) {
            std::cout << "RenderComponent don't have Geometry or Shader!" << std::endl;
            return;
        }
        
        // 关键：先绑定 Shader，确保后续 uniform 设置到正确的 shader
        m_Shader->Bind();
        
        // 1. 设置基础矩阵
        m_Shader->SetUniformMat4fv("proj_matrix", projectionMatrix);
        m_Shader->SetUniformMat4fv("mv_matrix", viewMatrix * modelMatrix);
        
        if (m_NeedsNormalMatrix) {
            glm::mat4 normalMatrix = glm::transpose(glm::inverse(viewMatrix * modelMatrix));
            m_Shader->SetUniformMat4fv("norm_matrix", normalMatrix);
        }
        
        // 2. 应用所有组件的 uniform 数据
        ApplyAllComponentsToShader(*m_Shader);
        
        // 3. 执行渲染
        if (m_Texture) {
            renderer.Draw(*m_Geometry, *m_Shader, *m_Texture);
        } else {
            renderer.Draw(*m_Geometry, *m_Shader);
        }
    }

    // 其他成员保持不变...
    void SetGeometry(std::shared_ptr<Shaper> geometry) { m_Geometry = geometry; }
    void SetShader(std::shared_ptr<Shader> shader) { m_Shader = shader; }
    void SetTexture(std::shared_ptr<Texture> texture) { m_Texture = texture; }
    
    std::shared_ptr<Shaper> GetGeometry() const { return m_Geometry; }
    std::shared_ptr<Shader> GetShader() const { return m_Shader; }
    std::shared_ptr<Texture> GetTexture() const { return m_Texture; }
    
    void SetNeedsNormalMatrix(bool needs) { m_NeedsNormalMatrix = needs; }
    bool GetNeedsNormalMatrix() const { return m_NeedsNormalMatrix; }

private:
    std::shared_ptr<Shaper> m_Geometry;
    std::shared_ptr<Shader> m_Shader;          // 共享资源
    std::shared_ptr<Texture> m_Texture;
    bool m_NeedsNormalMatrix = false;
private:
    //应用实体所有组件的 uniform 数据
    void ApplyAllComponentsToShader(Shader& shader) {
        if (auto owner = GetOwner()) {
            // 遍历实体的所有组件，调用它们的 ApplyToShader 方法
            for (auto& [type, component] : owner->GetAllComponents()) {
                component->ApplyToShader(shader);
            }
        }
    }
};