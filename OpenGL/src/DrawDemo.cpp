#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "DrawDemo.h"

#include "Utility.h"
#include "Texture.h"
#include "Renderer.h"

#include "AllShaperTypes.h"
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

	glm::mat4 rotatemtx = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // 创建一个绕Z轴旋转45度的矩阵


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




void DrawCube(GLFWwindow* window,bool enbaleAnimation)
{


    // 红色立方体顶点数据（每个顶点：位置x,y,z，颜色r,g,b，纹理u,v）
    GLfloat vertices[] = {
        // 前面
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        // 后面
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
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


    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));
    VertexBufferLayout layout({ (float)3 });
	va.LinkBufferAndLayout(vb, layout);

    Shader shader("res/shaders/Cube.shader");
    shader.Bind();
    
	// 获取窗口的宽度和高度
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;


    // 在渲染前设置MVP
    glm::mat4 model = model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-5.0f));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.5f, -3.0f)); // 摄像机后退3单位
    glm::mat4 mv= view * model;

    glm::mat4 projection = glm::perspective(glm::radians(70.0f), aspect, 0.1f, 100.0f);






    Renderer renderer;
	renderer.SetPolygonMode(false).SetDepthTest(true); //启动线框模式和深度测试

    while (!glfwWindowShouldClose(window))
    {
		auto currentTime = static_cast<float>(glfwGetTime());
        if (enbaleAnimation)
        {
            glm::mat4 tMat = glm::translate(glm::mat4(1.0f), glm::vec3(sin(0.35 * currentTime) * 2.0f, cos(0.52f * currentTime) * 2.0f, sin(0.7f * currentTime) * 2.0f)); //平移不会改变大小
            //glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), 1.75f * currentTime * currentTime, glm::vec3(0.0f, 0.0f, 1.0f)); 试试二次曲线，旋转速度随时间增大而增大而不是纯线性增大，挺有意思的
            glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), 1.75f * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
            rMat = glm::rotate(rMat, 1.75f * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
            rMat = glm::rotate(rMat, 1.75f * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
			//1.75f * currentTime是旋转速度，可以根据需要调整

			glm::mat4 mMat = tMat * rMat ; // 先平移后旋转

            shader.SetUniformMat4fv("mv_matrix", mMat*mv);
            shader.SetUniformMat4fv("proj_matrix", projection);

        }
        else
        {
            shader.SetUniformMat4fv("mv_matrix", mv);
            shader.SetUniformMat4fv("proj_matrix", projection);
        }


        renderer.Clear();
        renderer.Draw(va,ib,shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
 

}


void DrawMultiCube(GLFWwindow* window, bool enbaleAnimation)
{


    // 红色立方体顶点数据（每个顶点：位置x,y,z，颜色r,g,b，纹理u,v）
    GLfloat vertices[] = {
        // 前面
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        // 后面
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
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


    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));
    VertexBufferLayout layout({ (float)3 });
    va.LinkBufferAndLayout(vb, layout);

    Shader shader("res/shaders/Cube.shader");
    shader.Bind();

    // 获取窗口的宽度和高度
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;


    // 在渲染前设置MVP
    glm::mat4 model = model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.5f, -3.0f)); // 摄像机后退3单位
    glm::mat4 mv = view * model;

    glm::mat4 projection = glm::perspective(glm::radians(70.0f), aspect, 0.1f, 100.0f);






    Renderer renderer;
    renderer.SetPolygonMode(false).SetDepthTest(true); //启动线框模式和深度测试

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        for(int i =0 ;i<24;i++)
        {
            auto currentTime = static_cast<float>(glfwGetTime());
            auto tf = i + currentTime;
            if (enbaleAnimation)
            {
                glm::mat4 tMat = glm::translate(glm::mat4(1.0f), glm::vec3(sin(0.35 * tf) * 8.0f, cos(0.52f * tf) * 8.0f, sin(0.7f * tf) * 8.0f)); //平移不会改变大小
                //glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), 1.75f * currentTime * currentTime, glm::vec3(0.0f, 0.0f, 1.0f)); 试试二次曲线，旋转速度随时间增大而增大而不是纯线性增大，挺有意思的
                glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), 1.75f * tf ,glm::vec3(0.0f, 0.0f, 1.0f));
                rMat = glm::rotate(rMat, 1.75f * tf, glm::vec3(0.0f, 1.0f, 0.0f));
                rMat = glm::rotate(rMat, 1.75f * tf, glm::vec3(1.0f, 0.0f, 0.0f));
                //1.75f * currentTime是旋转速度，可以根据需要调整

                glm::mat4 mMat = tMat * rMat; // 先平移后旋转

                shader.SetUniformMat4fv("mv_matrix", mMat * mv);
                shader.SetUniformMat4fv("proj_matrix", projection);

            }
            else
            {
                shader.SetUniformMat4fv("mv_matrix", mv);
                shader.SetUniformMat4fv("proj_matrix", projection);
            }
            renderer.Draw(va, ib, shader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


}


void DrawMultiCubeIntances(GLFWwindow* window, bool enbaleAnimation)
{

    // 红色立方体顶点数据（每个顶点：位置x,y,z，颜色r,g,b，纹理u,v）
    GLfloat vertices[] = {
        // 前面
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        // 后面
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
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


    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));
    VertexBufferLayout layout({ (float)3 });
    va.LinkBufferAndLayout(vb, layout);

    Shader shader("res/shaders/CubeMultiInstances.shader");
    shader.Bind();

    // 获取窗口的宽度和高度
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;


    // 在渲染前设置MVP
    glm::mat4 model = model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -420.0f)); // 摄像机后退420单位
    glm::mat4 mv = view * model;

    glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect, 0.1f, 100.0f);


    Renderer renderer;
    renderer.SetPolygonMode(false).SetDepthTest(true); //启动线框模式和深度测试

    while (!glfwWindowShouldClose(window))
    {
        auto currentTime = static_cast<float>(glfwGetTime());
        shader.SetUniformMat4fv("v_matrix", mv);
		shader.SetUniformMat4fv("proj_matrix", projection);
		shader.SetUniform1f("tf", currentTime);

        renderer.Clear();
        renderer.DrawInstanced(va, ib, shader, 100000);

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


}

void DrawCube_And_Pyramid(GLFWwindow* window, bool enbaleAnimation)
{

    
    Cube cube;
    Shader shader("res/shaders/Cube.shader");

    // 获取窗口的宽度和高度
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;


    // 在渲染前设置MVP
    glm::mat4 model = model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.5f, -3.0f)); // 摄像机后退3单位
    glm::mat4 mv = view * model;

    glm::mat4 projection = glm::perspective(glm::radians(70.0f), aspect, 0.1f, 100.0f);






    Renderer renderer;
    renderer.SetPolygonMode(false).SetDepthTest(true); //启动线框模式和深度测试

    while (!glfwWindowShouldClose(window))
    {
        auto currentTime = static_cast<float>(glfwGetTime());
        if (enbaleAnimation)
        {
            glm::mat4 tMat = glm::translate(glm::mat4(1.0f), glm::vec3(sin(0.35 * currentTime) * 2.0f, cos(0.52f * currentTime) * 2.0f, sin(0.7f * currentTime) * 2.0f)); //平移不会改变大小
            //glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), 1.75f * currentTime * currentTime, glm::vec3(0.0f, 0.0f, 1.0f)); 试试二次曲线，旋转速度随时间增大而增大而不是纯线性增大，挺有意思的
            glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), 1.75f * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
            rMat = glm::rotate(rMat, 1.75f * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
            rMat = glm::rotate(rMat, 1.75f * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
            //1.75f * currentTime是旋转速度，可以根据需要调整

            glm::mat4 mMat = tMat * rMat; // 先平移后旋转

            shader.SetUniformMat4fv("mv_matrix", mMat * mv);
            shader.SetUniformMat4fv("proj_matrix", projection);

        }
        else
        {
            shader.SetUniformMat4fv("mv_matrix", mv);
            shader.SetUniformMat4fv("proj_matrix", projection);
        }


        renderer.Clear();
        renderer.Draw(cube.GetVertexArray(),cube.GetIndexBuffer(), shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


}
