#pragma once
/* This Class is a wrapper class for OpenGL shader programs.
 * It handles the loading, compiling, and linking of shaders,
 * as well as providing an interface for setting shader uniforms.
 */
#include <string>
#include <Resource.h>
#include <unordered_map>
#include <glm/ext/matrix_float4x4.hpp>
#include <fstream>
#include <sstream>


struct ShaderProgramSource
{
	std::string vertexShader;
	std::string fragmentShader;
};




class Shader :public Resource
{
public:
	Shader() = default;
	Shader(const std::string& flle_path);
	~Shader();

	void Bind() const override;
	void Unbind() const override;

	// Set uniform values
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniformMat4fv(const std::string& name, const glm::mat4& matrix);


private:
	std::string m_FilePath;
	ShaderProgramSource ParseShaderSource(const std::string filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);

	int GetUniformLocation(const std::string& name) const;
	

	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
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
