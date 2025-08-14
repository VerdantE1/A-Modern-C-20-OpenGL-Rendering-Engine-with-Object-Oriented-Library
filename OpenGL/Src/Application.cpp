#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Utility.h>
#include <Renderer.h>


int main(void)
{
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
        //---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    unsigned int indices[] = {
        0, 1, 2, // First triangle
        2, 3, 0  // Second triangle
    };



    /* Vertex Define*/
    VertexArray va;                                 //VAO
    VertexBuffer vb(vertices, sizeof(vertices));    //VBO
    VertexBufferLayout layout({ (float)3,(float)3,(float)2 });         //Layout
    va.LinkBufferAndLayout(vb, layout);             //vb interpreted by var layout

    /* Index Define */
    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

    /* Shader Define*/
    Shader shader("res/shaders/Basic.shader");

    /* Texture Define*/
    Texture texture_1("res/textures/Texture1.jpg");
    texture_1.Bind(); //Bind ourTexture in 0 slot
    shader.SetUniform1i("u_Texture1", texture_1.GetAssignedSlot());  //We need let shader know where we bind ourtexture


    Texture texture_2("res/textures/Texture2.jpg");
    texture_2.Bind(); //Bind ourTexture in 1 slot
    shader.SetUniform1i("u_Texture2", texture_2.GetAssignedSlot());  //We need let shader know where we bind ourtexture






    /* Initializing */
    UnbindAll(va, vb, ib, shader);

    Renderer renderer;



    /* User Setting -Color */
    float r = 0.0f;
    float increment = 0.01f; // Increment value for the red color component


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        renderer.Clear();
        renderer.Draw(va, ib, shader);


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
    }
   
    //======================================================================
    std::cout << "Loop exited. Terminating." << std::endl;
    glfwTerminate();
    return 0;
}



