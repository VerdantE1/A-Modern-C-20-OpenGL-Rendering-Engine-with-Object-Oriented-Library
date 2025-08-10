#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Utility.h"
#include <Render.h>

template<typename... Args> static void BindAll(const Args&...  args);
template<typename... Args> static void UnbindAll(const Args&...  args);
template <typename T> constexpr bool has_unbind_v = requires(T t) { t.Unbind(); };
template <typename T> constexpr bool has_bind_v = requires (T t) { t.Bind(); };


int main(void)
{
    GLFWwindow* window;

    /* Initialize the GLFW library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use the core profile of OpenGL

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

	

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

   glfwSwapInterval(1);// Enable vsync (vertical synchronization) to limit the frame rate to the monitor's refresh rate

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

    
   
 
    /* Vertex Define*/
    VertexArray va;                                 //VAO
    VertexBuffer vb(vertices, sizeof(vertices));    //VBO
    VertexBufferLayout layout({(float) 3});         //Layout
    va.LinkBufferAndLayout(vb, layout);             //vb interpreted by var layout
  
    /* Index Define */
    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

    /* Shader Define*/
    Shader shader("res/shaders/Basic.shader");
    

    
    /* Initializing */
    UnbindAll(va, vb, ib, shader);

    /* User Setting -Color */
    float r = 0.0f;
	float increment = 0.01f; // Increment value for the red color component
	

    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));   

        BindAll(va, vb, ib, shader);
        



		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0)); // Draw the triangles using the vertex indices in the IBO
		//glDrawArrays(GL_TRIANGLES, 0, 3); // Draw the triangle using the vertex data in the VBO
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        if (r > 1.0f)
            increment = -increment; // Reverse the increment direction if r exceeds 1.0f
        else if (r < 0.0f)
            increment = -increment;
        r += increment;

        /* Swap front and back buffers */
        GLCall(glfwSwapBuffers(window));

        /* Poll for and process events */
        GLCall(glfwPollEvents());



    }

   
    //======================================================================
    
    GLCall(glfwTerminate());
    return 0;
}



template<typename... Args>
static void UnbindAll(const Args&...  args)  
{
    static int idx = 0;
    auto lambda = [&](const auto& a) {
        if constexpr (has_unbind_v<decltype(a)>)
            a.Unbind();
        else
            std::cout << "Warning! " << idx << "parameter don't have Unbind Member!" << std::endl;      
        };
    (lambda(args),...);

}


template<typename... Args>
static void BindAll(const Args&...  args)
{
	static int idx = 0;
	auto lambda = [&](const auto& a) {
		if constexpr (has_unbind_v<decltype(a)>)
			a.Bind();
		else
			std::cout << "Warning! " << idx << "parameter don't have Bind Member!" << std::endl;
		};
	(lambda(args), ...);

}