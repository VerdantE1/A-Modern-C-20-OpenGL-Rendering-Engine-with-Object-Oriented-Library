#pragma once
/* This Class is a wrapper class for OpenGL shader programs.
 * It handles the loading, compiling, and linking of shaders,
 * as well as providing an interface for setting shader uniforms.
 */
#include <string>
#include <Resource.h>
#include <Utility.h>
#include <unordered_map>

struct ShaderProgramSource
{
	std::string vertexShader;
	std::string fragmentShader;
};




class Shader :public Resource
{
public:
	Shader(const std::string& flle_path);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniform values
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	std::string m_FilePath;
	ShaderProgramSource ParseShaderSource(const std::string filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);

	int GetUniformLocation(const std::string& name) const;
	

	mutable std::unordered_map<std::string, int> m_UniformLocationCache;
};