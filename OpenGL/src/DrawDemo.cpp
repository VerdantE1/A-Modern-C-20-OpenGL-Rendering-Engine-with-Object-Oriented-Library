#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Utility.h>
#include <Renderer.h>
#include "DrawDemo.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "./2D/IsoscelesTriangle.h"


void DrawDemo(GLFWwindow* window)
{
    // �������������
    GLfloat vertices[] = {
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout({ (float)3, (float)3, (float)2 });
    va.LinkBufferAndLayout(vb, layout);

    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));
    Shader shader("res/shaders/Basic.shader");

    Texture texture_1("res/textures/Texture1.jpg");
    texture_1.Bind();
    shader.SetUniform1i("u_Texture1", texture_1.GetAssignedSlot());

    Texture texture_2("res/textures/Texture2.jpg");
    texture_2.Bind();
    shader.SetUniform1i("u_Texture2", texture_2.GetAssignedSlot());

    UnbindAll(va, vb, ib, shader);

    Renderer renderer;

    float r = 0.0f;
    float increment = 0.01f;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        renderer.Draw(va, ib, shader);

        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        if (r > 1.0f)
            increment = -increment;
        else if (r < 0.0f)
            increment = -increment;
        r += increment;

        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }
}



void DrawCube(GLFWwindow* window)
{
	float cameraX, cameraY, cameraZ;
	float cubeLocX, cubeLocY, cubeLocZ;

	// ���������λ��
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f; // �����λ��
	cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f; // ���������������������е�λ��

    // ��ɫ�����嶥�����ݣ�ÿ�����㣺λ��x,y,z����ɫr,g,b������u,v��
    GLfloat vertices[] = {
        // ǰ��
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   
        // ����
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,  
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   
        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,  
    };

    // �������������ݣ�ÿ�������������Σ���12�������Σ�
    unsigned int indices[] = {
        // ǰ��
        0, 1, 2, 2, 3, 0,
        // ����
        1, 5, 6, 6, 2, 1,
        // ����
        5, 4, 7, 7, 6, 5,
        // ����
        4, 0, 3, 3, 7, 4,
        // ����
        3, 2, 6, 6, 7, 3,
        // ����
        4, 5, 1, 1, 0, 4
    };

    // ������ֱ������Щ���ݴ���VAO/VBO/IBO����Ⱦ
    VertexArray va;

	VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout({ (float)3, (float)3});
    va.LinkBufferAndLayout(vb, layout);
    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

    /*������ͨ���߼�,�����index��ͨ�õģ�������ɫ�ǹ̶���ɫ*/
    

    Shader shader("res/shaders/Basic.shader");
    
    // ����͸�Ӿ���
	int width, height;
	glfwGetFramebufferSize(window, &width, &height); // ��ȡ���ڵĿ�Ⱥ͸߶�
	float aspect = (float)width / (float)height;
	glm::mat4 pMat= glm::perspective(1.0f, aspect, 0.1f, 1000.0f); // 1.0472f��60�ȵĻ���ֵ

    // ������ͼ����ģ�;����MV����
	glm::mat vMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)); // �任�������λ�á�����ƶ�3����λ
	glm::mat mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ)); // �任���������λ�á����������ƶ�

	shader.SetUniformMat4fv("u_MvMatrix", vMat * mMat); // ����MV����
	shader.SetUniformMat4fv("u_ProjMatrix", pMat); // ����ͶӰ����

    
    //UnbindAll(va, vb, ib, shader);
    Renderer renderer;
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // ��ɫ
    while (!glfwWindowShouldClose(window))
    {
		glEnable(GL_DEPTH_TEST); // ������Ȳ���
        glDepthFunc(GL_LEQUAL);
        renderer.Clear();
        renderer.Draw(va, ib, shader);



        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }
    

}

void DrawPoint(GLFWwindow* window)
{
    VertexArray vao;

    Shader shader("res/shaders/OnePoint.shader");
    Renderer renderer;

    while(!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        BindAll(vao, shader);
		GLCall(glPointSize(100.0f)); 
        GLCall(glDrawArrays(GL_POINTS, 0, 1));
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
	}

}

void DrawAnimationOnePoint_Scale(GLFWwindow* window)
{
    VertexArray vao;

    Shader shader("res/shaders/OnePoint.shader");
    Renderer renderer;

    float pointsize = 10.0f;
    float inc = 1.0f;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        BindAll(vao, shader);

		if (pointsize > 100.0f || pointsize < 10.0f) inc = -inc; // ���Ƶ��С��10��100֮��
		pointsize += inc; // ���ӻ���ٵ��С

        GLCall(glPointSize(pointsize));
        GLCall(glDrawArrays(GL_POINTS, 0, 1));
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }

}

void DrawTriangle(GLFWwindow* window)
{
    VertexArray vao;
    //Shader shader("res/shaders/OnePoint.shader");
	Shader shader("res/shaders/Triangle.shader");
    Renderer renderer;
    while(!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        BindAll(vao, shader);
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }
}

void DrawTriangleIsosceles(GLFWwindow* window)
{
	IsoscelesTriangle triangle; // ʹ��IsoscelesTriangle��
    Shader shader("res/shaders/GeneralTriangle.shader");
    Renderer renderer;

    while (!glfwWindowShouldClose(window))
    {
        triangle.Draw(shader,renderer);

        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }
}


void DrawAnimationTrianlge_Move(GLFWwindow* window)
{

    VertexArray vao;
    Shader shader("res/shaders/AnimationTriangle.shader");

    float xpos = 0.0f;
    float inc = 0.01f;

 

    Renderer renderer;

    while(!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        BindAll(vao, shader);

        if (xpos > 1.0f || xpos<-1.0f) inc = -inc;
        xpos += inc;


		shader.SetUniform1f("offset", xpos); // ����xλ��

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }
}

void DrawAnimationTrianlge_Move(GLFWwindow* window, float currentTime)
{

    VertexArray vao;
    Shader shader("res/shaders/AnimationTriangle.shader");

    // ��������
    float amplitude = 0.8f; // ����ƶ�����
    float speed = 1.0f;     // �ٶ�����



    Renderer renderer;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        BindAll(vao, shader);

        // ���㵱ǰ֡��xλ��
        float xpos = amplitude * sin(speed * currentTime);
        shader.SetUniform1f("offset", xpos); // ����xλ��

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());

        // ���� currentTime
        currentTime = static_cast<float>(glfwGetTime());
    }
}

void DrawSolarSystem(GLFWwindow* windows)
{


}


