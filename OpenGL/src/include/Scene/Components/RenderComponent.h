#pragma once
#include "Component.h"
#include "Shaper.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include <memory>
#include <iostream>
#include "MaterialComponent.h"

class RenderComponent : public Component {
public:
    RenderComponent() = default;
    
    RenderComponent(std::shared_ptr<Shaper> geometry, 
                   std::shared_ptr<Shader> shader,
                   std::shared_ptr<Texture> texture = nullptr)
        : m_Geometry(geometry), m_Shader(shader), m_Texture(texture) {}
    
    // 渲染方法
    void Render(const Renderer& renderer, 
               const glm::mat4& projectionMatrix, 
               const glm::mat4& viewMatrix, 
               const glm::mat4& modelMatrix) {
        if (!m_Geometry || !m_Shader) {
            std::cout << "RendererComponent don't have Geometry or Shader!" << std::endl;
            return; // 缺少必要资源
        }
        
        // 设置矩阵uniforms
        m_Shader->SetUniformMat4fv("proj_matrix", projectionMatrix);
        m_Shader->SetUniformMat4fv("mv_matrix", viewMatrix * modelMatrix);
        
        // 如果有法线矩阵需求（光照）
        if (m_NeedsNormalMatrix) {
            glm::mat4 normalMatrix = glm::transpose(glm::inverse(viewMatrix * modelMatrix));
            m_Shader->SetUniformMat4fv("norm_matrix", normalMatrix);
        }
        
        // 设置材质属性（如果实体有MaterialComponent）
        if (auto material = GetOwner()->GetComponent<MaterialComponent>()) {
            m_Shader->SetUniform4f("material.ambient", 
                material->ambient.r, material->ambient.g, material->ambient.b, material->ambient.a);
            m_Shader->SetUniform4f("material.diffuse", 
                material->diffuse.r, material->diffuse.g, material->diffuse.b, material->diffuse.a);
            m_Shader->SetUniform4f("material.specular", 
                material->specular.r, material->specular.g, material->specular.b, material->specular.a);
            m_Shader->SetUniform1f("material.shininess", material->shininess);
        }
        
        // 渲染
        if (m_Texture) {
            renderer.Draw(*m_Geometry, *m_Shader, *m_Texture);
        } else {
            renderer.Draw(*m_Geometry, *m_Shader);
        }
    }
    
    // 设置资源
    void SetGeometry(std::shared_ptr<Shaper> geometry) { m_Geometry = geometry; }
    void SetShader(std::shared_ptr<Shader> shader) { m_Shader = shader; }
    void SetTexture(std::shared_ptr<Texture> texture) { m_Texture = texture; }
    
    // 获取资源
    std::shared_ptr<Shaper> GetGeometry() const { return m_Geometry; }
    std::shared_ptr<Shader> GetShader() const { return m_Shader; }
    std::shared_ptr<Texture> GetTexture() const { return m_Texture; }
    
    // 控制是否需要法线矩阵（用于光照）
    void SetNeedsNormalMatrix(bool needs) { m_NeedsNormalMatrix = needs; }
    bool GetNeedsNormalMatrix() const { return m_NeedsNormalMatrix; }

private:
    std::shared_ptr<Shaper> m_Geometry;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Texture> m_Texture;
    bool m_NeedsNormalMatrix = false;
};