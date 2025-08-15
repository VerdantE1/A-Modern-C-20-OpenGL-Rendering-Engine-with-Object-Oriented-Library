#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>




class Transform
{
public:
    // Move this outside the class as a free function

    friend glm::mat4 operator*(const glm::mat4& m, const Transform& t);

    Transform() = default;

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
