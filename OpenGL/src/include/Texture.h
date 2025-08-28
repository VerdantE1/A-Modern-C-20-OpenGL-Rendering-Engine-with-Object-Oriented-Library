#pragma once
#include "Resource.h"
#include <string>
#include <unordered_set>
#include <glm/glm.hpp>


typedef int GLint;

// 纹理过滤模式枚举
enum class TextureFilterMode {
    NEAREST,                // 最近点采样
    LINEAR,                 // 线性过滤
    NEAREST_MIPMAP_NEAREST, // 最近的mipmap层级，并使用最近点采样
    LINEAR_MIPMAP_NEAREST,  // 最近的mipmap层级，并使用线性过滤
    NEAREST_MIPMAP_LINEAR,  // 在mipmap层级之间插值，每层使用最近点采样
    LINEAR_MIPMAP_LINEAR    // 在mipmap层级之间插值，每层使用线性过滤（质量最高）
};

// 纹理环绕模式枚举
enum class TextureWrapMode {
    REPEAT,          // 重复
    MIRRORED_REPEAT, // 镜像重复
    CLAMP_TO_EDGE,   // 边缘拉伸
    CLAMP_TO_BORDER  // 使用边框颜色
};

// 各向异性过滤级别枚举
enum class AnisotropyLevel {
    NONE = 0,        // 不使用各向异性过滤
    LOW = 2,         // 低级别各向异性过滤 (2x)
    MEDIUM = 4,      // 中级别各向异性过滤 (4x)
    HIGH = 8,        // 高级别各向异性过滤 (8x)
    VERY_HIGH = 16   // 非常高级别各向异性过滤 (16x)
};


/*
* Texture will be assigned in orderly from 0 start. This is force for unifying the bind interface.
*/
class Texture : public Resource
{
private:
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_Bpp;
    unsigned int m_AssignedSlot = -1; // This Slot AssignedSlot by Renderer
    
    // 新增：存储各向异性过滤等级
    float m_AnisotropyLevel = 1.0f;
    
    // Track available texture slots
    static std::unordered_set<unsigned int> s_AvailableSlots;
    static unsigned int s_MaxSlotUsed;
    
    // 静态成员：检查并存储是否支持各向异性过滤及最大支持级别
    static bool s_AnisotropyChecked;
    static bool s_AnisotropySupported;
    static float s_MaxAnisotropy;

    // 辅助函数，将枚举转换为OpenGL常量
    GLint GetGLFilterMode(TextureFilterMode mode) const;
    GLint GetGLWrapMode(TextureWrapMode mode) const;
    
    // 检查各向异性过滤支持
    static void CheckAnisotropySupport();

public:
    Texture() = default;
    
    // 带有完整参数的构造函数，增加了各向异性过滤参数
    Texture(const std::string& filepath, 
            TextureFilterMode magFilter = TextureFilterMode::LINEAR, 
            TextureFilterMode minFilter = TextureFilterMode::LINEAR,
            TextureWrapMode wrapS = TextureWrapMode::CLAMP_TO_EDGE,
            TextureWrapMode wrapT = TextureWrapMode::CLAMP_TO_EDGE,
            bool generateMipmaps = false,
            bool flipVertically = true,
            AnisotropyLevel anisotropy = AnisotropyLevel::NONE);
    
    ~Texture();

    void Bind() const override; 
    void Unbind() const override;

    // 设置边框颜色（当使用CLAMP_TO_BORDER模式时）
    void SetBorderColor(const glm::vec4& color);
    
    // 设置各向异性过滤级别
    void SetAnisotropyLevel(AnisotropyLevel level);
    void SetAnisotropyLevel(float level);
    
    // 获取各向异性过滤设置
    float GetAnisotropyLevel() const { return m_AnisotropyLevel; }
    
    // 获取是否支持各向异性过滤和最大支持级别
    static bool IsAnisotropySupported() { 
        if (!s_AnisotropyChecked) CheckAnisotropySupport();
        return s_AnisotropySupported; 
    }
    
    static float GetMaxAnisotropy() { 
        if (!s_AnisotropyChecked) CheckAnisotropySupport();
        return s_MaxAnisotropy; 
    }

    // Getter方法
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline int GetBpp() const { return m_Bpp; } 
    inline unsigned int GetAssignedSlot() const { return m_AssignedSlot; }
    
    // 静态方法
    static unsigned int GetNextAvailableSlot();
    static void ReleaseSlot(unsigned int slot);
};




/* Example Usage:

// 默认设置
Texture defaultTexture("res/textures/brick1.jpg");

// 使用各向异性过滤的纹理
Texture anisotropicTexture("res/textures/floor.jpg",
    TextureFilterMode::LINEAR,
    TextureFilterMode::LINEAR_MIPMAP_LINEAR,
    TextureWrapMode::REPEAT,
    TextureWrapMode::REPEAT,
    true,  // 生成mipmap
    true,  // 垂直翻转
    AnisotropyLevel::HIGH);  // 高级别各向异性过滤

// 检查是否支持各向异性过滤
if (Texture::IsAnisotropySupported()) {
    std::cout << "Anisotropic filtering supported! Max level: " 
              << Texture::GetMaxAnisotropy() << "x" << std::endl;
}

*/
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
