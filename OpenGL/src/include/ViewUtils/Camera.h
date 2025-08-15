#pragma once
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

struct FrustumRect {
	float left, right, bottom, top, z;
};

inline std::ostream& operator<<(std::ostream& os, const FrustumRect& rect) {
	os << "FrustumRect: ["
		<< "left=" << rect.left << ", right=" << rect.right
		<< ", bottom=" << rect.bottom << ", top=" << rect.top
		<< ", z=" << rect.z << "]";
	return os;
}


class Camera
{
public:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
	float fov, aspect, near, far;

	Camera(const glm::vec3& pos, const glm::vec3& tgt, const glm::vec3& upVec, float fovAngle, float aspectRatio, float nearPlane, float farPlane)
		: position(pos), target(tgt), up(upVec), fov(fovAngle), aspect(aspectRatio), near(nearPlane), far(farPlane) {
	}

	glm::mat4 GetViewMatrix() const {
		return glm::lookAt(position, target, up);
	}

	glm::mat4 GetProjectionMatrix() const {
		return glm::perspective(glm::radians(fov), aspect, near, far);
	}




	// 给定任意z，计算该z平面上的裁剪范围
	FrustumRect GetFrustumRectAtZ(float z) const {
		float half_fovy = glm::radians(fov) * 0.5f;
		float tan_half_fovy = tan(half_fovy);
		float abs_z = std::abs(z);

		float h = tan_half_fovy * abs_z;
		float w = h * aspect;
		return FrustumRect{
			-w, +w,
			-h, +h,
			z
		};
	}

	// 返回近平面的FrustumRect
	FrustumRect GetNearFrustumRect() const {
		return GetFrustumRectAtZ(-near);
	}

	// 返回远平面的FrustumRect
	FrustumRect GetFarFrustumRect() const {
		return GetFrustumRectAtZ(-far);
	}
};

