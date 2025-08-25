#include "Utility.h"
#include "Globals.h"
#include "Shader.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cerr << "[OpenGL Error] (" << error << "): " << "in "
			<< function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}


void installLights(const glm::mat4 vMatrix,Shader& shader)
{
	//将光源位置从世界空间转换到视图空间坐标,并存入浮点数组
	lightPosV = glm::vec3(vMatrix * glm::vec4(currentLightPos, 1.0));
	lightPos[0] = lightPosV.x;
	lightPos[1] = lightPosV.y;
	lightPos[2] = lightPosV.z;

	// 设置全局环境光
	shader.SetUniform4f("globalAmbient", globalAmbient[0], globalAmbient[1], globalAmbient[2], globalAmbient[3]);

	// 设置光源属性
	shader.SetUniform4f("light.ambient", lightAmbient[0], lightAmbient[1], lightAmbient[2], lightAmbient[3]);
	shader.SetUniform4f("light.diffuse", lightDiffuse[0], lightDiffuse[1], lightDiffuse[2], lightDiffuse[3]);
	shader.SetUniform4f("light.specular", lightSpecular[0], lightSpecular[1], lightSpecular[2], lightSpecular[3]);
	shader.SetUniform3f("light.position", lightPos[0], lightPos[1], lightPos[2]);

	// 设置材质属性
	shader.SetUniform4f("material.ambient", matAmb[0], matAmb[1], matAmb[2], matAmb[3]);
	shader.SetUniform4f("material.diffuse", matDif[0], matDif[1], matDif[2], matDif[3]);
	shader.SetUniform4f("material.specular", matSpe[0], matSpe[1], matSpe[2], matSpe[3]);
	shader.SetUniform1f("material.shininess", matShi);

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
