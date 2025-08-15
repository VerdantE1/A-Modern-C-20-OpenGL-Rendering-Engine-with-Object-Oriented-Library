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


    
    // ���ɻ򷵻ر任����
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
        // �Ȼ�ø��Եľ���
        glm::mat4 m = getMatrix() * rhs.getMatrix();
        // ��ȡ�±任��������ʵ�֣�ֻ����󣬲��ֽ������
        result.setMatrix(m);
        return result;
    }

    
    glm::mat4 operator*(const glm::mat4& m) const {
        return getMatrix() * m;
    }


private:
    glm::vec3 position{ 0.0f, 0.0f, 0.0f };    // λ��
    glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };    // ŷ���ǣ�x=Pitch, y=Yaw, z=Roll����λ�����ȣ�
    glm::vec3 scale{ 1.0f, 1.0f, 1.0f };       // ����

    mutable glm::mat4 mat{ 1.0f };             // �����õ�mat4
    mutable bool dirty{ true };                // �����仯ʱdirty���Զ�����mat
};

//Support for Transform multiplication with glm::mat4
inline glm::mat4 operator*(const glm::mat4& m, const Transform& t) {
    return m * t.getMatrix();
}
