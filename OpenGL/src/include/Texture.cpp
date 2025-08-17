#include "Texture.h"
#include "vendor/stb_image/stb_image.h"
#include "Utility.h"

// 初始化静态成员
std::unordered_set<unsigned int> Texture::s_AvailableSlots;
unsigned int Texture::s_MaxSlotUsed = 0;
bool Texture::s_AnisotropyChecked = false;
bool Texture::s_AnisotropySupported = false;
float Texture::s_MaxAnisotropy = 1.0f;

// 检查各向异性过滤支持
void Texture::CheckAnisotropySupport()
{
    if (s_AnisotropyChecked) return;
    
    // 检查是否支持各向异性过滤扩展
    s_AnisotropySupported = glewIsSupported("GL_EXT_texture_filter_anisotropic");
    
    if (s_AnisotropySupported) {
        // 获取最大支持的各向异性级别
        GLCall(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &s_MaxAnisotropy));
    }
    
    s_AnisotropyChecked = true;
}

unsigned int Texture::GetNextAvailableSlot()
{
    // If we have reusable slots, use one of those
    if (!s_AvailableSlots.empty()) {
        unsigned int slot = *s_AvailableSlots.begin();
        s_AvailableSlots.erase(s_AvailableSlots.begin());
        return slot;
    }
    
    // Otherwise, assign a new slot
    return s_MaxSlotUsed++;
}

void Texture::ReleaseSlot(unsigned int slot)
{
    // Make the slot available for reuse
    s_AvailableSlots.insert(slot);
    
    // If this was the highest slot and no other slots are in use,
    // we can reduce s_MaxSlotUsed
    if (slot == s_MaxSlotUsed - 1) {
        s_MaxSlotUsed--;
        // Check if we can reduce further (if more high slots were previously released)
        while (s_MaxSlotUsed > 0 && s_AvailableSlots.find(s_MaxSlotUsed - 1) != s_AvailableSlots.end()) {
            s_AvailableSlots.erase(s_MaxSlotUsed - 1);
            s_MaxSlotUsed--;
        }
    }
}

Texture::Texture(const std::string& filepath, 
                TextureFilterMode magFilter, 
                TextureFilterMode minFilter,
                TextureWrapMode wrapS,
                TextureWrapMode wrapT,
                bool generateMipmaps,
                bool flipVertically,
                AnisotropyLevel anisotropy)
    : m_FilePath(filepath), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_Bpp(0), 
      m_AssignedSlot(GetNextAvailableSlot())
{
    // 确保已检查各向异性过滤支持
    if (!s_AnisotropyChecked) {
        CheckAnisotropySupport();
    }
    
    // 设置各向异性过滤级别
    m_AnisotropyLevel = static_cast<float>(anisotropy);
    if (m_AnisotropyLevel > s_MaxAnisotropy) {
        m_AnisotropyLevel = s_MaxAnisotropy;
    }
    
    // 设置是否垂直翻转纹理
    stbi_set_flip_vertically_on_load(flipVertically);
    
    // 加载图像数据
    m_LocalBuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_Bpp, 4); // 4表示RGBA格式
    
    if (!m_LocalBuffer)
    {
        std::cerr << "Failed to load texture: " << filepath << std::endl;
        return;
    }

    // 创建纹理对象
    GLCall(glGenTextures(1, &m_id));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
    
    // 设置纹理过滤参数
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetGLFilterMode(magFilter)));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetGLFilterMode(minFilter)));
    
    // 设置纹理环绕方式
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetGLWrapMode(wrapS)));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetGLWrapMode(wrapT)));
    
    // 如果支持并启用了各向异性过滤
    if (s_AnisotropySupported && m_AnisotropyLevel > 1.0f) {
        GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, m_AnisotropyLevel));
    }
    
    // 将图像数据绑定到GPU内存
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
    
    // 根据需要生成mipmap
    if (generateMipmaps) {
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    }

    // 激活纹理单元并绑定纹理
    GLCall(glActiveTexture(GL_TEXTURE0 + m_AssignedSlot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_id));

    // 释放本地缓冲
    if (m_LocalBuffer)
    {
        stbi_image_free(m_LocalBuffer);
        m_LocalBuffer = nullptr;
    }
}

Texture::~Texture()
{
    // Release the assigned slot back to the pool
    if (m_AssignedSlot != -1) {
        ReleaseSlot(m_AssignedSlot);
    }
    
    GLCall(glDeleteTextures(1, &m_id));
}

void Texture::Bind() const
{
    if (m_AssignedSlot == -1)
    {
        std::cerr << "Texture Bind error: This Texture instance is not assigned yet for some unknown reason!" << std::endl;
        return;
    }
    GLCall(glActiveTexture(GL_TEXTURE0 + m_AssignedSlot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

// 设置边框颜色
void Texture::SetBorderColor(const glm::vec4& color)
{
    GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
    GLCall(glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &color[0]));
}

// 设置各向异性过滤级别 (枚举版本)
void Texture::SetAnisotropyLevel(AnisotropyLevel level)
{
    if (!s_AnisotropyChecked) {
        CheckAnisotropySupport();
    }
    
    if (!s_AnisotropySupported) {
        return; // 如果不支持，则直接返回
    }
    
    float newLevel = static_cast<float>(level);
    if (newLevel > s_MaxAnisotropy) {
        newLevel = s_MaxAnisotropy;
    }
    
    if (m_AnisotropyLevel != newLevel) {
        m_AnisotropyLevel = newLevel;
        
        GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
        GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, m_AnisotropyLevel));
    }
}

// 设置各向异性过滤级别 (浮点版本)
void Texture::SetAnisotropyLevel(float level)
{
    if (!s_AnisotropyChecked) {
        CheckAnisotropySupport();
    }
    
    if (!s_AnisotropySupported) {
        return; // 如果不支持，则直接返回
    }
    
    if (level < 1.0f) level = 1.0f; // 至少为1.0
    if (level > s_MaxAnisotropy) level = s_MaxAnisotropy; // 不超过最大支持级别
    
    if (m_AnisotropyLevel != level) {
        m_AnisotropyLevel = level;
        
        GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
        GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, m_AnisotropyLevel));
    }
}

// 将枚举转换为OpenGL过滤模式常量
GLint Texture::GetGLFilterMode(TextureFilterMode mode) const
{
    switch (mode)
    {
        case TextureFilterMode::NEAREST:
            return GL_NEAREST;
        case TextureFilterMode::LINEAR:
            return GL_LINEAR;
        case TextureFilterMode::NEAREST_MIPMAP_NEAREST:
            return GL_NEAREST_MIPMAP_NEAREST;
        case TextureFilterMode::LINEAR_MIPMAP_NEAREST:
            return GL_LINEAR_MIPMAP_NEAREST;
        case TextureFilterMode::NEAREST_MIPMAP_LINEAR:
            return GL_NEAREST_MIPMAP_LINEAR;
        case TextureFilterMode::LINEAR_MIPMAP_LINEAR:
            return GL_LINEAR_MIPMAP_LINEAR;
        default:
            return GL_LINEAR;
    }
}

// 将枚举转换为OpenGL环绕模式常量
GLint Texture::GetGLWrapMode(TextureWrapMode mode) const
{
    switch (mode)
    {
        case TextureWrapMode::REPEAT:
            return GL_REPEAT;
        case TextureWrapMode::MIRRORED_REPEAT:
            return GL_MIRRORED_REPEAT;
        case TextureWrapMode::CLAMP_TO_EDGE:
            return GL_CLAMP_TO_EDGE;
        case TextureWrapMode::CLAMP_TO_BORDER:
            return GL_CLAMP_TO_BORDER;
        default:
            return GL_CLAMP_TO_EDGE;
    }
}


/*
 * Copyright (c) 2025 
 * Email: 2523877046@qq.com
 * Author: Baiqiang Long (Buzzlight)
 * 
 * This file is part of the ReduxGL project.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
