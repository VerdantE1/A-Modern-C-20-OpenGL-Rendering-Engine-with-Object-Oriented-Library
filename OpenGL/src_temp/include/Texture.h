#pragma once
#include "Resource.h"
#include <string>
#include <unordered_set>
#include <glm/glm.hpp>


typedef int GLint;

// �������ģʽö��
enum class TextureFilterMode {
    NEAREST,                // ��������
    LINEAR,                 // ���Թ���
    NEAREST_MIPMAP_NEAREST, // �����mipmap�㼶����ʹ����������
    LINEAR_MIPMAP_NEAREST,  // �����mipmap�㼶����ʹ�����Թ���
    NEAREST_MIPMAP_LINEAR,  // ��mipmap�㼶֮���ֵ��ÿ��ʹ����������
    LINEAR_MIPMAP_LINEAR    // ��mipmap�㼶֮���ֵ��ÿ��ʹ�����Թ��ˣ�������ߣ�
};

// ������ģʽö��
enum class TextureWrapMode {
    REPEAT,          // �ظ�
    MIRRORED_REPEAT, // �����ظ�
    CLAMP_TO_EDGE,   // ��Ե����
    CLAMP_TO_BORDER  // ʹ�ñ߿���ɫ
};

// �������Թ��˼���ö��
enum class AnisotropyLevel {
    NONE = 0,        // ��ʹ�ø������Թ���
    LOW = 2,         // �ͼ���������Թ��� (2x)
    MEDIUM = 4,      // �м���������Թ��� (4x)
    HIGH = 8,        // �߼���������Թ��� (8x)
    VERY_HIGH = 16   // �ǳ��߼���������Թ��� (16x)
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
    
    // �������洢�������Թ��˵ȼ�
    float m_AnisotropyLevel = 1.0f;
    
    // Track available texture slots
    static std::unordered_set<unsigned int> s_AvailableSlots;
    static unsigned int s_MaxSlotUsed;
    
    // ��̬��Ա����鲢�洢�Ƿ�֧�ָ������Թ��˼����֧�ּ���
    static bool s_AnisotropyChecked;
    static bool s_AnisotropySupported;
    static float s_MaxAnisotropy;

    // ������������ö��ת��ΪOpenGL����
    GLint GetGLFilterMode(TextureFilterMode mode) const;
    GLint GetGLWrapMode(TextureWrapMode mode) const;
    
    // ���������Թ���֧��
    static void CheckAnisotropySupport();

public:
    Texture() = default;
    
    // �������������Ĺ��캯���������˸������Թ��˲���
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

    // ���ñ߿���ɫ����ʹ��CLAMP_TO_BORDERģʽʱ��
    void SetBorderColor(const glm::vec4& color);
    
    // ���ø������Թ��˼���
    void SetAnisotropyLevel(AnisotropyLevel level);
    void SetAnisotropyLevel(float level);
    
    // ��ȡ�������Թ�������
    float GetAnisotropyLevel() const { return m_AnisotropyLevel; }
    
    // ��ȡ�Ƿ�֧�ָ������Թ��˺����֧�ּ���
    static bool IsAnisotropySupported() { 
        if (!s_AnisotropyChecked) CheckAnisotropySupport();
        return s_AnisotropySupported; 
    }
    
    static float GetMaxAnisotropy() { 
        if (!s_AnisotropyChecked) CheckAnisotropySupport();
        return s_MaxAnisotropy; 
    }

    // Getter����
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline int GetBpp() const { return m_Bpp; } 
    inline unsigned int GetAssignedSlot() const { return m_AssignedSlot; }
    
    // ��̬����
    static unsigned int GetNextAvailableSlot();
    static void ReleaseSlot(unsigned int slot);
};




/* Example Usage:

// Ĭ������
Texture defaultTexture("res/textures/brick1.jpg");

// ʹ�ø������Թ��˵�����
Texture anisotropicTexture("res/textures/floor.jpg",
    TextureFilterMode::LINEAR,
    TextureFilterMode::LINEAR_MIPMAP_LINEAR,
    TextureWrapMode::REPEAT,
    TextureWrapMode::REPEAT,
    true,  // ����mipmap
    true,  // ��ֱ��ת
    AnisotropyLevel::HIGH);  // �߼���������Թ���

// ����Ƿ�֧�ָ������Թ���
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
