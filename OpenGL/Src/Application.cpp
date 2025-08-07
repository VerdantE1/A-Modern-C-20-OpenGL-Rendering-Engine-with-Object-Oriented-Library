#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cerr << "[OpenGL Error] (" << error << "): " << "in "
			<< function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

#define ASSERT(X) if (!(X)) __debugbreak(); // Accept one predicate expression X and break if it is false
#define GLCall(X) GLClearError();\
    X;\
    ASSERT(GLLogCall(#X,__FILE__,__LINE__));\


struct ShaderProgramSource
{
    std::string vertexShader;
    std::string fragmentShader;
};


static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader_id = 0;
    if (!(shader_id = glCreateShader(type)))
    {
        std::cerr << "Error creating shader" << std::endl;
		return 0;
    }
	const char* src = source.c_str();
    glShaderSource(shader_id,1,&src,nullptr);
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
            <<" shader!" << std::endl;

        std::cout << message << std::endl;
		glDeleteShader(shader_id);
        return 0;

    }
    return shader_id;


}


static ShaderProgramSource ParseShader(const std::string filepath)
{
    enum class ShaderType
    {
        None = -1,
		Vertex = 0,
		Fragment = 1
    };
	ShaderType currentShaderType = ShaderType::None;

    std::ifstream stream(filepath,std::ios::in);
    if(!stream.is_open())
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
            if(line.find("vertex") != std::string::npos)
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

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program_id = glCreateProgram(); // Create a new program object and return its ID
    if (program_id == 0)
    {
        std::cerr << "Error creating program" << std::endl;
		return 0;
    }

    /* Compile the vertex and fragment shaders if they are provided */
    unsigned int vs =0, fs = 0;
	
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
    glGetProgramiv(program_id, GL_LINK_STATUS,&linkStatus);

    if(linkStatus == GL_FALSE)
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


int main(void)
{
    GLFWwindow* window;

    /* Initialize the GLFW library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    /* Initialize the GLEW library*/
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error initializing GLEW" << std::endl;
        return -1;
    }

	std::cout << "GLEW initialized successfully" << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;    

	//======================================================================
    //Main Code


	// Define the vertices for a triangle
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,  //0
         0.5f, -0.5f, 0.0f,  //1
         0.5f, 0.5f, 0.0f,   //2
        -0.5f, 0.5f,  0.0f   //3
	};

    unsigned int indices[] = {
        0, 1, 2, // First triangle
        2, 3, 0  // Second triangle
	};


    GLuint vbo;
    GLCall(glGenBuffers(1, &vbo));  // Generate(Construct) a buffer object in GPU memory
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo)); // Bind (Active) the buffer object which should be process for GL machine to the GL_ARRAY_BUFFER target
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW)); //(Initialize) Copy the vertex data to the buffer object in GPU memory

    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0)); // Define the vertex attribute pointer for the vertex data
    GLCall(glEnableVertexAttribArray(0)); // Enable the vertex attribute array at index 0 


	GLuint ibo;
    GLCall(glGenBuffers(1, &ibo));  // Generate(Construct) a buffer object in GPU memory
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo)); // Bind (Active) the buffer object which should be process for GL machine to the Vertex array indices target
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW)); //(Initialize) Copy the vertex data to the buffer object in GPU memory


    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
	//std::cout << source.vertexShader << std::endl;
	//std::cout << source.fragmentShader << std::endl;

	unsigned int shader = CreateShader(source.vertexShader, source.fragmentShader);
	GLCall(glUseProgram(shader));


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));


		//glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle using the vertex data in the VBO
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0)); // Draw the triangles using the vertex indices in the IBO



        /* Swap front and back buffers */
        GLCall(glfwSwapBuffers(window));

        /* Poll for and process events */
        GLCall(glfwPollEvents());
    }

   
    //======================================================================
    
    GLCall(glfwTerminate());
    return 0;
}

