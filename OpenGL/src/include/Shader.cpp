#include <Shader.h>
#include "Utility.h"
#include <fstream>
#include <sstream>



Shader::Shader(const std::string& file_path):m_FilePath(file_path)
{
	
	ShaderProgramSource source = ParseShaderSource(file_path);
	m_id = CreateShader(source.vertexShader, source.fragmentShader); //Create and Compile 
	GLCall(glUseProgram(m_id));

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
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4fv(const std::string& name, const glm::mat4& matrix)
{
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
		std::cerr << "Error opening shader file: " << filepath << std::endl;
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
				std::cout << "Vertex Shader found" << std::endl;
				// Handle vertex shader code
			}
			else if (line.find("fragment") != std::string::npos)
			{
				currentShaderType = ShaderType::Fragment;
				std::cout << "Fragment Shader found" << std::endl;
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
		std::cerr << "Error creating program" << std::endl;
		return 0;
	}

	/* Compile the vertex and fragment shaders if they are provided */
	unsigned int vs = 0, fs = 0;

	if (vertexShader != "")
	{
		vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		if (vs == 0)
		{
			std::cout << "Vertex shader compilation failed" << std::endl;
			glDeleteProgram(program_id);
			return 0;
		}
	}

	if (fragmentShader != "")
	{
		fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
		if (fs == 0)
		{
			std::cout << "Fragment shader compilation failed" << std::endl;
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
		std::cerr << "Error linking program" << std::endl;
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

	return program_id;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int shader_id = 0;
	if (!(shader_id = glCreateShader(type)))
	{
		std::cerr << "Error creating shader" << std::endl;
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
		// Print the error message to standard error
		std::cerr << "Error compiling shader: " <<
			(type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader")
			<< " shader!" << std::endl;

		std::cout << message << std::endl;
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
		std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
	
	m_UniformLocationCache[name] = location;
	return location;
}

