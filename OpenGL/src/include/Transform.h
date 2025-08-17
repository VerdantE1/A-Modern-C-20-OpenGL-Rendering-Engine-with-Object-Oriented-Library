#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>




class Transform
{
public:
    // Move this outside the class as a free function

    friend glm::mat4 operator*(const glm::mat4& m, const Transform& t);

    Transform() = default;
    Transform(glm::mat4 rhs ) {
		setMatrix(rhs); // 默认构造函数，允许mat4->Transform转换
    }

    void setPosition(float x, float y, float z) { 
        position = glm::vec3(x, y, z);
        dirty = true; 
    }
    void setRotation(float pitch, float yaw, float roll) { 
        rotation = glm::vec3(pitch, yaw, roll); 
        dirty = true;
    }
	void setScale(float sx, float sy, float sz) { 
        scale = glm::vec3(sx, sy, sz);
        dirty = true;
    }

    void setMatrix(const glm::mat4& m) {
        mat = m;
        dirty = false;
    }

	const float getWorldX() const { return position.x; }
	const float getWorldY() const { return position.y; }
	const float getWorldZ() const { return position.z; }   
	const glm::vec3& getPosition() const { return position; }
	const glm::vec3& getRotation() const { return rotation; }


    
    // 生成或返回变换矩阵
    const glm::mat4& getMatrix() const {
        if (dirty) {
            mat = glm::mat4(1.0f);
            mat = glm::translate(mat, position);
            mat = glm::rotate(mat, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            mat = glm::rotate(mat, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            mat = glm::rotate(mat, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
            mat = glm::scale(mat, scale);
            dirty = false;
        }
        return mat;
    }

   
    Transform operator*(const Transform& rhs) const {
        Transform result;
        // 先获得各自的矩阵
        glm::mat4 m = getMatrix() * rhs.getMatrix();
        // 提取新变换参数（简单实现：只存矩阵，不分解参数）
        result.setMatrix(m);
        return result;
    }

    
    glm::mat4 operator*(const glm::mat4& m) const {
        return getMatrix() * m;
    }


private:
    glm::vec3 position{ 0.0f, 0.0f, 0.0f };    // 位置
    glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };    // 欧拉角：x=Pitch, y=Yaw, z=Roll（单位：弧度）
    glm::vec3 scale{ 1.0f, 1.0f, 1.0f };       // 缩放

    mutable glm::mat4 mat{ 1.0f };             // 缓存用的mat4
    mutable bool dirty{ true };                // 参数变化时dirty，自动更新mat
};

//Support for Transform multiplication with glm::mat4
inline glm::mat4 operator*(const glm::mat4& m, const Transform& t) {
    return m * t.getMatrix();
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
