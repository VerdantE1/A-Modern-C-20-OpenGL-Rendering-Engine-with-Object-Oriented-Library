#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>



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

static unsigned int CreateProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program_id = 0; // Create a new program object and return its ID
    if (program_id == glCreateProgram())
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
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
	};


    GLuint VBOidx;
	glGenBuffers(1, &VBOidx);  // Generate(Construct) a buffer object in GPU memory
	glBindBuffer(GL_ARRAY_BUFFER, VBOidx); // Bind (Active) the buffer object which should be process for GL machine to the GL_ARRAY_BUFFER target
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //(Initialize) Copy the vertex data to the buffer object in GPU memory

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0); // Define the vertex attribute pointer for the vertex data
	glEnableVertexAttribArray(0); // Enable the vertex attribute array at index 0 即0号顶点属性槽【状态】 Buffer里面存在顶点属性，我们仅启用顶点属性槽0


    std::string vertexShader = 
        "#version 330 core\n"
        "\n"
        "layout (location = 0) in vec3 position;\n" //从位于Buffer里的顶点属性槽0读取数据。
		"void main()\n"
        "{\n"
		"    gl_Position = vec4(position.x , position.y ,position.z ,1.0);\n" //gl_Position是一个内置变量(built-in variable)，表示顶点在裁剪空间中的位置。
		"}\n";

    std::string fragmentShader = 
		"#version 330 core\n"
		"\n"
		"layout (location = 0) out vec4 color;\n" 
		"void main()\n"
		"{\n"
		"    color = vec4(1.0, 0.0 ,0.0 , 1.0);\n"
		"}\n";
    unsigned int shader = CreateProgram(vertexShader,fragmentShader);
    glUseProgram(shader);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle using the vertex data in the VBO


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    
    //======================================================================
    
    glfwTerminate();
    return 0;
}

