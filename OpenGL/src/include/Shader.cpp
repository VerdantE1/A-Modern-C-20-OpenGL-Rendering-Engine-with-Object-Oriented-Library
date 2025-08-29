#include <Shader.h>
#include "Logger.h"  // 先包含Logger
#include "Utility.h" // 后包含Utility，避免循环依赖问题
#include <fstream>
#include <sstream>


Shader::Shader(const std::string& file_path):m_FilePath(file_path)
{
	LOG_DEBUG("Creating shader from: {}", file_path);
	
	ShaderProgramSource source = ParseShaderSource(file_path);
	m_id = CreateShader(source.vertexShader, source.fragmentShader);
	
	if (m_id == 0) {
		LOG_CRITICAL("Shader creation failed for: {}", file_path);
		throw std::runtime_error("Shader creation failed");
	}
	
	glUseProgram(m_id);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		LOG_ERROR("OpenGL error using shader {}: {}", m_id, error);
	}
	
	LOG_INFO("Shader created successfully: {}", file_path);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_id));

}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_id));
}

void Shader::Unbind() const
{
	this->Bind();
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	this->Bind();
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	this->Bind();
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	this->Bind();
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	this->Bind();
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniformMat4fv(const std::string& name, const glm::mat4& matrix)
{
	this->Bind();
	int location = GetUniformLocation(name);
	GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}



ShaderProgramSource Shader::ParseShaderSource(const std::string filepath)
{
	enum class ShaderType
	{
		None = -1,
		Vertex = 0,
		Fragment = 1
	};
	ShaderType currentShaderType = ShaderType::None;

	std::ifstream stream(filepath, std::ios::in);
	if (!stream.is_open())
	{
		LOG_ERROR("	Shader:	Error opening shader file: {}", filepath);
		return {};
	}
	std::string line;
	std::stringstream ss[2]; // 0 for vertex shader, 1 for fragment shader

	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				currentShaderType = ShaderType::Vertex;
				LOG_INFO("\t\t\tShader: Vertex Shader found in file: {}", filepath);
				// Handle vertex shader code
			}
			else if (line.find("fragment") != std::string::npos)
			{
				currentShaderType = ShaderType::Fragment;
				LOG_INFO("\t\t\tShader:	Fragment Shader found in file: {}", filepath);
				// Handle fragment shader code
			}
		}
		else
		{
			ss[static_cast<int>(currentShaderType)] << line << "\n";
		}
	}
	return { ss[0].str(),ss[1].str() };

}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program_id = glCreateProgram(); // Create a new program object and return its ID
	if (program_id == 0)
	{
		LOG_ERROR("Shader:	Error creating shader program");
		return 0;
	}

	/* Compile the vertex and fragment shaders if they are provided */
	unsigned int vs = 0, fs = 0;

	if (vertexShader != "")
	{
		vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		if (vs == 0)
		{
			LOG_ERROR("Shader:	Vertex shader compilation failed");
			glDeleteProgram(program_id);
			return 0;
		}
	}

	if (fragmentShader != "")
	{
		fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
		if (fs == 0)
		{
			LOG_ERROR("Shader:	Fragment shader compilation failed");
			glDeleteProgram(program_id);
			return 0;
		}
	}

	/* Attach the shaders to the program */
	glAttachShader(program_id, vs);
	glAttachShader(program_id, fs);

	/* Link the program */
	glLinkProgram(program_id);
	int linkStatus;
	glGetProgramiv(program_id, GL_LINK_STATUS, &linkStatus);

	if (linkStatus == GL_FALSE)
	{
		LOG_ERROR("Shader:	Error linking shader program");
		glDeleteProgram(program_id);
		return 0;
	}

	/* Detach and delete the shaders */
	for (auto shader : { vs,fs })
	{
		if (shader != 0)
		{
			glDeleteShader(shader);
		}
	}
	LOG_SUCCESS("Shader: Shader program created successfully with ID {}", program_id);
	return program_id;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int shader_id = 0;
	if (!(shader_id = glCreateShader(type)))
	{
		LOG_ERROR("Shader:	Error creating shader of type {}", type);
		return 0;
	}
	const char* src = source.c_str();
	glShaderSource(shader_id, 1, &src, nullptr);
	glCompileShader(shader_id);

	int compileStatus;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		int length;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader_id, length, &length, message);

		LOG_FAILED("	Shader: Error compiling {} shader! {}",
			(type == GL_VERTEX_SHADER ? "Vertex" : "Fragment"), message);

		glDeleteShader(shader_id);
		return 0;

	}
	return shader_id;



}

int Shader::GetUniformLocation(const std::string& name) const
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location =glGetUniformLocation(m_id, name.c_str())); 
	if (location == -1)
		LOG_WARN("Shader:Warning: uniform {} doesn't exist!", name);
	
	m_UniformLocationCache[name] = location;
	return location;
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
