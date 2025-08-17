#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "DrawDemo.h"

#include "Utility.h"
#include "Texture.h"
#include "Renderer.h"

#include "Camera.h"

#include "AllShaperTypes.h"
#include <Transform.h>
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


    


    // To this, explicitly specify all constructor parameters to avoid ambiguity:
    Texture texture_1(
        "res/textures/Texture1.jpg",
        TextureFilterMode::LINEAR, 
        TextureFilterMode::LINEAR,
        TextureWrapMode::CLAMP_TO_EDGE,
        TextureWrapMode::CLAMP_TO_EDGE,
        false, // generateMipmaps
        true   // flipVertically
    );


    shader.SetUniform1i("u_Texture1", texture_1.GetAssignedSlot());
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
    Shader shader("res/shaders/Cube.shader");
 
    Cube cube;
	Pyramid pyramid;


    // MVP设置同 Cube
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;

    // 摄像机初始化
    Camera camera(
        glm::vec3(0, 0, 3), // position
        glm::vec3(0, 0, 0),  // target
        glm::vec3(0, 1, 0),  // up
        70.0f, aspect, 0.1f, 100.0f
    );


    // 初始化物体的Transform
    Transform cubeTransform;
    cubeTransform.setPosition(0.0f, 0.0f, -5.0f); // 立方体后移

    Transform pyramidTransform;
    pyramidTransform.setPosition(0.0f, -2.0f, -5.0f); // 金字塔偏下

	glm::mat4 view = camera.GetViewMatrix();              //View Matrix
	glm::mat4 projection = camera.GetProjectionMatrix();  //Projection Matrix

    Renderer renderer;
    renderer.SetPolygonMode(false).SetDepthTest(true); //启动线框模式和深度测试

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        float currentTime = static_cast<float>(glfwGetTime());

        // ====== Cube绘制 ======
        glm::mat4 cubeMV = view * cubeTransform.getMatrix();

        // 动画：旋转 + 圆周运动
        float animAngle = 1.75f * currentTime;
        float animX = sin(0.35f * currentTime) * 2.0f;
        float animY = cos(0.52f * currentTime) * 2.0f;
        float animZ = sin(0.7f * currentTime) * 2.0f;

        // 更新Transform属性
        cubeTransform.setPosition(animX, animY, animZ - 5.0f);
        cubeTransform.setRotation(0.0f, animAngle, animAngle);

        //std::cout << camera.GetFrustumRectAtZ(-5) << std::endl;

        // --- 设置shader & 绘制Cube ---
        shader.SetUniformMat4fv("mv_matrix", view * cubeTransform.getMatrix());
        shader.SetUniformMat4fv("proj_matrix", projection);

        renderer.Draw(cube, shader);

        // ====== Pyramid绘制 ======
        pyramidTransform.setRotation(animX, 0.0f, 0.0f);
        pyramidTransform.setScale(1.0f, 1.0f, 1.0f);     


        shader.SetUniformMat4fv("mv_matrix", view * pyramidTransform.getMatrix());
		renderer.Draw(pyramid,shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


}

void DrawPyramidWithTexture(GLFWwindow* window, bool enableAnimation)
{
    // 创建三个不同过滤模式的纹理以便比较效果
    Texture textureNearest("res/textures/brick1.jpg", 
        TextureFilterMode::NEAREST,  // 最近点过滤（像素化）
        TextureFilterMode::NEAREST); 
        
    Texture textureLinear("res/textures/brick1.jpg", 
        TextureFilterMode::LINEAR,   // 线性过滤（平滑）
        TextureFilterMode::LINEAR);
        
    Texture textureMipmap("res/textures/brick1.jpg", 
        TextureFilterMode::LINEAR, 
        TextureFilterMode::LINEAR_MIPMAP_LINEAR,  // 三线性过滤（最高质量）
        TextureWrapMode::REPEAT,
        TextureWrapMode::REPEAT,
        true);  // 生成mipmap

    Shader shader("res/shaders/3DShaderWithTexture.shader");
    Pyramid pyramid;

    // MVP设置同 Cube
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;

    // 摄像机初始化
    Camera camera(
        glm::vec3(0, 0, 3),   // position
        glm::vec3(0, 0, 0),   // target
        glm::vec3(0, 1, 0),   // up
        70.0f, aspect, 0.1f, 100.0f
    );

    Transform pyramidTransform;
    pyramidTransform.setPosition(0.0f, 0.0f, -5.0f); // 调整金字塔位置到中心

    glm::mat4 view = camera.GetViewMatrix();         // View Matrix
    glm::mat4 projection = camera.GetProjectionMatrix(); // Projection Matrix

    Renderer renderer;
    renderer.SetPolygonMode(false).SetDepthTest(true);

    // 放大缩小动画的参数
    float minScale = 0.2f;    // 最小缩放值
    float maxScale = 5.0f;    // 最大缩放值（放大5倍）
    float scaleSpeed = 0.5f;  // 缩放速度
    
    // 添加一个变量跟踪当前使用的纹理
    int currentTextureMode = 0;  // 0=最近点, 1=线性, 2=mipmap
    double lastKeyPressTime = 0.0;
    
    // 设置窗口标题以显示当前过滤模式
    glfwSetWindowTitle(window, "Texture Filter Mode: NEAREST");

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        float currentTime = static_cast<float>(glfwGetTime());
        
        // 按空格键切换纹理过滤模式
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && 
            (currentTime - lastKeyPressTime) > 0.3) {  // 防止连续触发
            
            currentTextureMode = (currentTextureMode + 1) % 3;
            lastKeyPressTime = currentTime;
            
            // 更新窗口标题以显示当前模式
            switch (currentTextureMode) {
                case 0:
                    glfwSetWindowTitle(window, "Texture Filter Mode: NEAREST (像素化)");
                    break;
                case 1:
                    glfwSetWindowTitle(window, "Texture Filter Mode: LINEAR (平滑)");
                    break;
                case 2:
                    glfwSetWindowTitle(window, "Texture Filter Mode: MIPMAP (三线性过滤)");
                    break;
            }
        }

        // 计算当前缩放值 - 使用正弦函数实现平滑的缩放动画
        float scale = 0.0f;
        
        if (enableAnimation) {
            // 计算缩放值在minScale和maxScale之间变化
            scale = minScale + (maxScale - minScale) * 
                   (sin(scaleSpeed * currentTime) * 0.5f + 0.5f);
        }
        else {
            scale = 1.0f;  // 不启用动画时使用默认大小
        }

        // 应用缩放和旋转
        float animAngle = 0.5f * currentTime;  // 缓慢旋转
        pyramidTransform.setRotation(0.0f, animAngle, 0.0f);  // 绕Y轴旋转
        pyramidTransform.setScale(scale, scale, scale);  // 设置缩放

        // 设置着色器矩阵
        shader.SetUniformMat4fv("proj_matrix", projection);
        shader.SetUniformMat4fv("mv_matrix", view * pyramidTransform.getMatrix());
        
        // 根据当前模式选择纹理
        switch (currentTextureMode) {
            case 0:
                renderer.Draw(pyramid, shader, textureNearest);
                break;
            case 1:
                renderer.Draw(pyramid, shader, textureLinear);
                break;
            case 2:
                renderer.Draw(pyramid, shader, textureMipmap);
                break;
        }

        // 在屏幕上显示当前缩放值和使用的过滤模式
        // 这需要一个文本渲染系统，如果没有，可以省略这部分
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Draw3PyramidsWithTextureControls(GLFWwindow* window)
{
    // 创建三个不同过滤模式的纹理
    Texture textureNearest("res/textures/cheese.jpg", 
        TextureFilterMode::NEAREST,  // 最近点过滤（像素化）
        TextureFilterMode::NEAREST,
        TextureWrapMode::REPEAT,
        TextureWrapMode::REPEAT);
        
    Texture textureLinear("res/textures/cheese.jpg", 
        TextureFilterMode::LINEAR,   // 线性过滤（平滑）
        TextureFilterMode::LINEAR,
        TextureWrapMode::REPEAT,
        TextureWrapMode::REPEAT);
        
    Texture textureMipmap("res/textures/cheese.jpg", 
        TextureFilterMode::LINEAR, 
        TextureFilterMode::LINEAR_MIPMAP_LINEAR,  // 三线性过滤（最高质量）
        TextureWrapMode::REPEAT,
        TextureWrapMode::REPEAT,
        true);  // 生成mipmap

    Shader shader("res/shaders/3DShaderWithTexture.shader");
    Pyramid pyramid;

    // MVP设置
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;

    // 摄像机初始化
    Camera camera(
        glm::vec3(0, 1, 10),   // 位置调高一点，向后移动以便看到三个金字塔
        glm::vec3(0, 0, 0),    // 目标点
        glm::vec3(0, 1, 0),    // 上向量
        70.0f, aspect, 0.1f, 100.0f
    );

    // 三个金字塔的Transform
    Transform pyramid1Transform;
    Transform pyramid2Transform;
    Transform pyramid3Transform;
    
    // 初始横向位置（水平排列）
    pyramid1Transform.setPosition(-4.0f, 0.0f, -10.0f);  // 左边
    pyramid2Transform.setPosition(0.0f, 0.0f, -10.0f);   // 中间
    pyramid3Transform.setPosition(4.0f, 0.0f, -10.0f);   // 右边
    
    // 应用一些初始旋转，使它们看起来不同
    pyramid1Transform.setRotation(10.0f, 0.0f, 0.0f);     // 标准朝向
    pyramid2Transform.setRotation(10.0f, 0.0f, 0.0f);    // Y轴旋转45度
    pyramid3Transform.setRotation(10.0f, 0.0f, 0.0f);   // Y轴旋转-45度

    glm::mat4 view = camera.GetViewMatrix();              // 视图矩阵
    glm::mat4 projection = camera.GetProjectionMatrix();  // 投影矩阵

    Renderer renderer;
    renderer.SetPolygonMode(false).SetDepthTest(true);    // 启用深度测试

    // 距离控制参数
    float moveSpeed = 0.4f;          // 移动速度
    float rotationSpeed = 0.05f;      // 旋转速度
    
    // 信息显示
    glfwSetWindowTitle(window, "3 Pyramids Demo | 按[W/S]键控制距离 | 按[A/D]键控制旋转");
    
    // 主循环
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        float currentTime = static_cast<float>(glfwGetTime());
        
        // 键盘输入处理 - 控制金字塔的距离
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            // W键 - 拉近金字塔
            pyramid1Transform.setPosition(
                pyramid1Transform.getPosition().x,
                pyramid1Transform.getPosition().y,
                pyramid1Transform.getPosition().z + moveSpeed);
                
            pyramid2Transform.setPosition(
                pyramid2Transform.getPosition().x,
                pyramid2Transform.getPosition().y,
                pyramid2Transform.getPosition().z + moveSpeed);
                
            pyramid3Transform.setPosition(
                pyramid3Transform.getPosition().x,
                pyramid3Transform.getPosition().y,
                pyramid3Transform.getPosition().z + moveSpeed);
        }
        
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            // S键 - 推远金字塔
            pyramid1Transform.setPosition(
                pyramid1Transform.getPosition().x,
                pyramid1Transform.getPosition().y,
                pyramid1Transform.getPosition().z - moveSpeed);
                
            pyramid2Transform.setPosition(
                pyramid2Transform.getPosition().x,
                pyramid2Transform.getPosition().y,
                pyramid2Transform.getPosition().z - moveSpeed);
                
            pyramid3Transform.setPosition(
                pyramid3Transform.getPosition().x,
                pyramid3Transform.getPosition().y,
                pyramid3Transform.getPosition().z - moveSpeed);
        }
        
        // 旋转控制
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            // A键 - 逆时针旋转
            pyramid1Transform.setRotation(
                pyramid1Transform.getRotation().x,
                pyramid1Transform.getRotation().y + rotationSpeed,
                pyramid1Transform.getRotation().z);
                
            pyramid2Transform.setRotation(
                pyramid2Transform.getRotation().x,
                pyramid2Transform.getRotation().y + rotationSpeed,
                pyramid2Transform.getRotation().z);
                
            pyramid3Transform.setRotation(
                pyramid3Transform.getRotation().x,
                pyramid3Transform.getRotation().y + rotationSpeed,
                pyramid3Transform.getRotation().z);
        }
        
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            // D键 - 顺时针旋转
            pyramid1Transform.setRotation(
                pyramid1Transform.getRotation().x,
                pyramid1Transform.getRotation().y - rotationSpeed,
                pyramid1Transform.getRotation().z);
                
            pyramid2Transform.setRotation(
                pyramid2Transform.getRotation().x,
                pyramid2Transform.getRotation().y - rotationSpeed,
                pyramid2Transform.getRotation().z);
                
            pyramid3Transform.setRotation(
                pyramid3Transform.getRotation().x,
                pyramid3Transform.getRotation().y - rotationSpeed,
                pyramid3Transform.getRotation().z);
        }
        
        // 计算当前Z位置，更新窗口标题显示信息
        std::string zPosStr = "Z位置: " + std::to_string(pyramid2Transform.getPosition().z);
        glfwSetWindowTitle(window, ("3 Pyramids Demo | W/S控制距离 | A/D控制旋转 | " + zPosStr).c_str());

        // 设置着色器投影矩阵（对所有金字塔相同）
        shader.SetUniformMat4fv("proj_matrix", projection);
        
        // 渲染第一个金字塔（最近点过滤）
        shader.SetUniformMat4fv("mv_matrix", view * pyramid1Transform.getMatrix());
        renderer.Draw(pyramid, shader, textureNearest);
        
        // 渲染第二个金字塔（线性过滤）
        shader.SetUniformMat4fv("mv_matrix", view * pyramid2Transform.getMatrix());
        renderer.Draw(pyramid, shader, textureLinear);
        
        // 渲染第三个金字塔（Mipmap过滤）
        shader.SetUniformMat4fv("mv_matrix", view * pyramid3Transform.getMatrix());
        renderer.Draw(pyramid, shader, textureMipmap);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}






void DrawSphere(GLFWwindow* window)
{
    Shader shader("res/shaders/Cube.shader");

    Cube cube;
    Pyramid pyramid;


    // MVP设置同 Cube
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;

    // 摄像机初始化
    Camera camera(
        glm::vec3(0, 0, 3), // position
        glm::vec3(0, 0, 0),  // target
        glm::vec3(0, 1, 0),  // up
        70.0f, aspect, 0.1f, 100.0f
    );


    // 初始化物体的Transform
    Transform cubeTransform;
    cubeTransform.setPosition(0.0f, 0.0f, -5.0f); // 立方体后移

    Transform pyramidTransform;
    pyramidTransform.setPosition(0.0f, -2.0f, -5.0f); // 金字塔偏下

    glm::mat4 view = camera.GetViewMatrix();              //View Matrix
    glm::mat4 projection = camera.GetProjectionMatrix();  //Projection Matrix

    Renderer renderer;
    renderer.SetPolygonMode(false).SetDepthTest(true); //启动线框模式和深度测试

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        float currentTime = static_cast<float>(glfwGetTime());

        // ====== Cube绘制 ======
        glm::mat4 cubeMV = view * cubeTransform.getMatrix();

        // 动画：旋转 + 圆周运动
        float animAngle = 1.75f * currentTime;
        float animX = sin(0.35f * currentTime) * 2.0f;
        float animY = cos(0.52f * currentTime) * 2.0f;
        float animZ = sin(0.7f * currentTime) * 2.0f;

        // 更新Transform属性
        cubeTransform.setPosition(animX, animY, animZ - 5.0f);
        cubeTransform.setRotation(0.0f, animAngle, animAngle);

        //std::cout << camera.GetFrustumRectAtZ(-5) << std::endl;

        // --- 设置shader & 绘制Cube ---
        shader.SetUniformMat4fv("mv_matrix", view * cubeTransform.getMatrix());
        shader.SetUniformMat4fv("proj_matrix", projection);

        renderer.Draw(cube, shader);

        // ====== Pyramid绘制 ======
        pyramidTransform.setRotation(animX, 0.0f, 0.0f);
        pyramidTransform.setScale(1.0f, 1.0f, 1.0f);


        shader.SetUniformMat4fv("mv_matrix", view * pyramidTransform.getMatrix());
        renderer.Draw(pyramid, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


}
