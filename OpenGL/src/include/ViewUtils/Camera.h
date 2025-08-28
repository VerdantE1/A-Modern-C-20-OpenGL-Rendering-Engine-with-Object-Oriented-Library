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
