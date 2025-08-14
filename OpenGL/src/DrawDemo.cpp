#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Utility.h>
#include <Renderer.h>
#include "Matrix.h"
#include "./2D/IsoscelesTriangle.h"
#include "DrawDemo.h"

void DrawDemo(GLFWwindow* window)
{
    // 顶点和索引数据
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

		if (pointsize > 100.0f || pointsize < 10.0f) inc = -inc; // 控制点大小在10到100之间
		pointsize += inc; // 增加或减少点大小

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

void DrawTriangleRotate(GLFWwindow* window)
{
    VertexArray vao;
    //Shader shader("res/shaders/OnePoint.shader");
    Shader shader("res/shaders/TriangleRotate.shader");
    Renderer renderer;

	glm::mat4 rotatemtx = buildRotateY(90.0f); // 初始化旋转矩阵

	shader.SetUniformMat4fv("transform", rotatemtx); // 设置初始旋转矩阵


    while (!glfwWindowShouldClose(window))
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
	IsoscelesTriangle triangle; // 使用IsoscelesTriangle类
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


		shader.SetUniform1f("offset", xpos); // 设置x位置

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
    }
}

void DrawAnimationTrianlge_Move(GLFWwindow* window, float currentTime)
{

    VertexArray vao;
    Shader shader("res/shaders/AnimationTriangle.shader");

    // 动画参数
    float amplitude = 0.8f; // 最大移动距离
    float speed = 1.0f;     // 速度因子



    Renderer renderer;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        BindAll(vao, shader);

        // 计算当前帧的x位置
        float xpos = amplitude * sin(speed * currentTime);
        shader.SetUniform1f("offset", xpos); // 设置x位置

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());

        // 更新 currentTime
        currentTime = static_cast<float>(glfwGetTime());
    }
}

void DrawSolarSystem(GLFWwindow* windows)
{


}




void DrawCube(GLFWwindow* window)
{


    // 红色立方体顶点数据（每个顶点：位置x,y,z，颜色r,g,b，纹理u,v）
    GLfloat vertices[] = {
        // 前面
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        // 后面
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    // 立方体索引数据（每个面两个三角形，共12个三角形）
    unsigned int indices[] = {
        // 前面
        0, 1, 2, 2, 3, 0,
        // 右面
        1, 5, 6, 6, 2, 1,
        // 后面
        5, 4, 7, 7, 6, 5,
        // 左面
        4, 0, 3, 3, 7, 4,
        // 上面
        3, 2, 6, 6, 7, 3,
        // 下面
        4, 5, 1, 1, 0, 4
    };


    // 创建VAO、VBO、EBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 绑定并上传数据
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 设置顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 加载编译shader（自行实现或用你自己的Shader类）
    // 假设你有Shader shader("Cube.vert", "Cube.frag");
    Shader shader("res/shaders/Cube.shader");
    shader.Bind();

    glEnable(GL_DEPTH_TEST);

    // 设置视口，建议窗口resize时也调用
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    while (!glfwWindowShouldClose(window))
    {

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Bind();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // 后续可直接用这些数据创建VAO/VBO/IBO并渲染
 //   VertexArray va;

    //VertexBuffer vb(vertices, sizeof(vertices));
 //   VertexBufferLayout layout({ (float)3});
 //   va.LinkBufferAndLayout(vb, layout);
 //   IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));

 //   /*上述是通用逻辑,顶点和index是通用的，就是颜色是固定红色*/
 //   

 //   Shader shader("res/shaders/Cube.shader");

 //   // 构建透视矩阵
    //int width, height;
    //glfwGetFramebufferSize(window, &width, &height); // 获取窗口的宽度和高度
    //float aspect = (float)width / (float)height;
    //glm::mat4 pMat= glm::perspective(1.0f, aspect, 0.1f, 1000.0f); // 1.0472f是60度的弧度值

 //   // 构建视图矩阵、模型矩阵和MV矩阵
    //glm::mat vMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)); // 变换摄像机的位置。向后移动3个单位
    //glm::mat mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ)); // 变换物体的世界位置。将立方体移动

    //shader.SetUniformMat4fv("u_MvMatrix", vMat * mMat); // 设置MV矩阵
    //shader.SetUniformMat4fv("u_ProjMatrix", pMat); // 设置投影矩阵


    //UnbindAll(va, vb, ib, shader);
  //  Renderer renderer;
  //  while (!glfwWindowShouldClose(window))
  //  {
  //      renderer.Clear();
        //glEnable(GL_DEPTH_TEST); // 启用深度测试
  //      glDepthFunc(GL_LEQUAL);
  //      BindAll(va, vb, ib, shader);
  //      GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr));


  //      GLCall(glfwSwapBuffers(window));
  //      GLCall(glfwPollEvents());
  //  }
  //  

}
