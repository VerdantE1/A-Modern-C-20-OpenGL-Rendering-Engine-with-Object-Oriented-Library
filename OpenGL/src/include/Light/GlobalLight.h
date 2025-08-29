#pragma once
#include "glm/fwd.hpp"
#include "Shader.h"
#include "Logger.h"

class GlobalLight {
public:
	glm::vec3 ambient = glm::vec3(0.1f);  // 基础环境光颜色
	glm::vec3 diffuse = glm::vec3(0.0f);  // 可选，通常全局光只用 ambient
	glm::vec3 specular = glm::vec3(0.0f); // 可选

	void ApplyToShader(Shader& shader) const {
		shader.SetUniform4f("globalAmbient", ambient.x, ambient.y, ambient.z,1.0f);
	}
	void SetAmbient(const glm::vec3& amb) {
		ambient = amb;
	}
	void SetDiffuse(const glm::vec3& diff) {
		diffuse = diff;
	}
	void SetSpecular(const glm::vec3& spec) {
		specular = spec;
	}
	void GetAmbient(glm::vec3& outAmb) const {
		outAmb = ambient;
	}

};
