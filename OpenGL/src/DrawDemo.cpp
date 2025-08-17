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

void DrawTriangleRotate(GLFWwindow* window)
{
    VertexArray vao;
    //Shader shader("res/shaders/OnePoint.shader");
    Shader shader("res/shaders/TriangleRotate.shader");
    Renderer renderer;

	glm::mat4 rotatemtx = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // ����һ����Z����ת45�ȵľ���


	shader.SetUniformMat4fv("transform", rotatemtx); // ���ó�ʼ��ת����


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

void DrawCube(GLFWwindow* window,bool enbaleAnimation)
{


    // ��ɫ�����嶥�����ݣ�ÿ�����㣺λ��x,y,z����ɫr,g,b������u,v��
    GLfloat vertices[] = {
        // ǰ��
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        // ����
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
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


    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));
    VertexBufferLayout layout({ (float)3 });
	va.LinkBufferAndLayout(vb, layout);

    Shader shader("res/shaders/Cube.shader");
    shader.Bind();
    
	// ��ȡ���ڵĿ�Ⱥ͸߶�
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;


    // ����Ⱦǰ����MVP
    glm::mat4 model = model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-5.0f));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.5f, -3.0f)); // ���������3��λ
    glm::mat4 mv= view * model;

    glm::mat4 projection = glm::perspective(glm::radians(70.0f), aspect, 0.1f, 100.0f);






    Renderer renderer;
	renderer.SetPolygonMode(false).SetDepthTest(true); //�����߿�ģʽ����Ȳ���

    while (!glfwWindowShouldClose(window))
    {
		auto currentTime = static_cast<float>(glfwGetTime());
        if (enbaleAnimation)
        {
            glm::mat4 tMat = glm::translate(glm::mat4(1.0f), glm::vec3(sin(0.35 * currentTime) * 2.0f, cos(0.52f * currentTime) * 2.0f, sin(0.7f * currentTime) * 2.0f)); //ƽ�Ʋ���ı��С
            //glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), 1.75f * currentTime * currentTime, glm::vec3(0.0f, 0.0f, 1.0f)); ���Զ������ߣ���ת�ٶ���ʱ���������������Ǵ���������ͦ����˼��
            glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), 1.75f * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
            rMat = glm::rotate(rMat, 1.75f * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
            rMat = glm::rotate(rMat, 1.75f * currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
			//1.75f * currentTime����ת�ٶȣ����Ը�����Ҫ����

			glm::mat4 mMat = tMat * rMat ; // ��ƽ�ƺ���ת

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


    // ��ɫ�����嶥�����ݣ�ÿ�����㣺λ��x,y,z����ɫr,g,b������u,v��
    GLfloat vertices[] = {
        // ǰ��
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        // ����
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
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


    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));
    VertexBufferLayout layout({ (float)3 });
    va.LinkBufferAndLayout(vb, layout);

    Shader shader("res/shaders/Cube.shader");
    shader.Bind();

    // ��ȡ���ڵĿ�Ⱥ͸߶�
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;


    // ����Ⱦǰ����MVP
    glm::mat4 model = model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.5f, -3.0f)); // ���������3��λ
    glm::mat4 mv = view * model;

    glm::mat4 projection = glm::perspective(glm::radians(70.0f), aspect, 0.1f, 100.0f);






    Renderer renderer;
    renderer.SetPolygonMode(false).SetDepthTest(true); //�����߿�ģʽ����Ȳ���

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        for(int i =0 ;i<24;i++)
        {
            auto currentTime = static_cast<float>(glfwGetTime());
            auto tf = i + currentTime;
            if (enbaleAnimation)
            {
                glm::mat4 tMat = glm::translate(glm::mat4(1.0f), glm::vec3(sin(0.35 * tf) * 8.0f, cos(0.52f * tf) * 8.0f, sin(0.7f * tf) * 8.0f)); //ƽ�Ʋ���ı��С
                //glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), 1.75f * currentTime * currentTime, glm::vec3(0.0f, 0.0f, 1.0f)); ���Զ������ߣ���ת�ٶ���ʱ���������������Ǵ���������ͦ����˼��
                glm::mat4 rMat = glm::rotate(glm::mat4(1.0f), 1.75f * tf ,glm::vec3(0.0f, 0.0f, 1.0f));
                rMat = glm::rotate(rMat, 1.75f * tf, glm::vec3(0.0f, 1.0f, 0.0f));
                rMat = glm::rotate(rMat, 1.75f * tf, glm::vec3(1.0f, 0.0f, 0.0f));
                //1.75f * currentTime����ת�ٶȣ����Ը�����Ҫ����

                glm::mat4 mMat = tMat * rMat; // ��ƽ�ƺ���ת

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

    // ��ɫ�����嶥�����ݣ�ÿ�����㣺λ��x,y,z����ɫr,g,b������u,v��
    GLfloat vertices[] = {
        // ǰ��
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        // ����
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
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


    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int));
    VertexBufferLayout layout({ (float)3 });
    va.LinkBufferAndLayout(vb, layout);

    Shader shader("res/shaders/CubeMultiInstances.shader");
    shader.Bind();

    // ��ȡ���ڵĿ�Ⱥ͸߶�
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;


    // ����Ⱦǰ����MVP
    glm::mat4 model = model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -420.0f)); // ���������420��λ
    glm::mat4 mv = view * model;

    glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect, 0.1f, 100.0f);


    Renderer renderer;
    renderer.SetPolygonMode(false).SetDepthTest(true); //�����߿�ģʽ����Ȳ���

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


    // MVP����ͬ Cube
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;

    // �������ʼ��
    Camera camera(
        glm::vec3(0, 0, 3), // position
        glm::vec3(0, 0, 0),  // target
        glm::vec3(0, 1, 0),  // up
        70.0f, aspect, 0.1f, 100.0f
    );


    // ��ʼ�������Transform
    Transform cubeTransform;
    cubeTransform.setPosition(0.0f, 0.0f, -5.0f); // ���������

    Transform pyramidTransform;
    pyramidTransform.setPosition(0.0f, -2.0f, -5.0f); // ������ƫ��

	glm::mat4 view = camera.GetViewMatrix();              //View Matrix
	glm::mat4 projection = camera.GetProjectionMatrix();  //Projection Matrix

    Renderer renderer;
    renderer.SetPolygonMode(false).SetDepthTest(true); //�����߿�ģʽ����Ȳ���

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        float currentTime = static_cast<float>(glfwGetTime());

        // ====== Cube���� ======
        glm::mat4 cubeMV = view * cubeTransform.getMatrix();

        // ��������ת + Բ���˶�
        float animAngle = 1.75f * currentTime;
        float animX = sin(0.35f * currentTime) * 2.0f;
        float animY = cos(0.52f * currentTime) * 2.0f;
        float animZ = sin(0.7f * currentTime) * 2.0f;

        // ����Transform����
        cubeTransform.setPosition(animX, animY, animZ - 5.0f);
        cubeTransform.setRotation(0.0f, animAngle, animAngle);

        //std::cout << camera.GetFrustumRectAtZ(-5) << std::endl;

        // --- ����shader & ����Cube ---
        shader.SetUniformMat4fv("mv_matrix", view * cubeTransform.getMatrix());
        shader.SetUniformMat4fv("proj_matrix", projection);

        renderer.Draw(cube, shader);

        // ====== Pyramid���� ======
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
    // ����������ͬ����ģʽ�������Ա�Ƚ�Ч��
    Texture textureNearest("res/textures/brick1.jpg", 
        TextureFilterMode::NEAREST,  // �������ˣ����ػ���
        TextureFilterMode::NEAREST); 
        
    Texture textureLinear("res/textures/brick1.jpg", 
        TextureFilterMode::LINEAR,   // ���Թ��ˣ�ƽ����
        TextureFilterMode::LINEAR);
        
    Texture textureMipmap("res/textures/brick1.jpg", 
        TextureFilterMode::LINEAR, 
        TextureFilterMode::LINEAR_MIPMAP_LINEAR,  // �����Թ��ˣ����������
        TextureWrapMode::REPEAT,
        TextureWrapMode::REPEAT,
        true);  // ����mipmap

    Shader shader("res/shaders/3DShaderWithTexture.shader");
    Pyramid pyramid;

    // MVP����ͬ Cube
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;

    // �������ʼ��
    Camera camera(
        glm::vec3(0, 0, 3),   // position
        glm::vec3(0, 0, 0),   // target
        glm::vec3(0, 1, 0),   // up
        70.0f, aspect, 0.1f, 100.0f
    );

    Transform pyramidTransform;
    pyramidTransform.setPosition(0.0f, 0.0f, -5.0f); // ����������λ�õ�����

    glm::mat4 view = camera.GetViewMatrix();         // View Matrix
    glm::mat4 projection = camera.GetProjectionMatrix(); // Projection Matrix

    Renderer renderer;
    renderer.SetPolygonMode(false).SetDepthTest(true);

    // �Ŵ���С�����Ĳ���
    float minScale = 0.2f;    // ��С����ֵ
    float maxScale = 5.0f;    // �������ֵ���Ŵ�5����
    float scaleSpeed = 0.5f;  // �����ٶ�
    
    // ���һ���������ٵ�ǰʹ�õ�����
    int currentTextureMode = 0;  // 0=�����, 1=����, 2=mipmap
    double lastKeyPressTime = 0.0;
    
    // ���ô��ڱ�������ʾ��ǰ����ģʽ
    glfwSetWindowTitle(window, "Texture Filter Mode: NEAREST");

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        float currentTime = static_cast<float>(glfwGetTime());
        
        // ���ո���л��������ģʽ
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && 
            (currentTime - lastKeyPressTime) > 0.3) {  // ��ֹ��������
            
            currentTextureMode = (currentTextureMode + 1) % 3;
            lastKeyPressTime = currentTime;
            
            // ���´��ڱ�������ʾ��ǰģʽ
            switch (currentTextureMode) {
                case 0:
                    glfwSetWindowTitle(window, "Texture Filter Mode: NEAREST (���ػ�)");
                    break;
                case 1:
                    glfwSetWindowTitle(window, "Texture Filter Mode: LINEAR (ƽ��)");
                    break;
                case 2:
                    glfwSetWindowTitle(window, "Texture Filter Mode: MIPMAP (�����Թ���)");
                    break;
            }
        }

        // ���㵱ǰ����ֵ - ʹ�����Һ���ʵ��ƽ�������Ŷ���
        float scale = 0.0f;
        
        if (enableAnimation) {
            // ��������ֵ��minScale��maxScale֮��仯
            scale = minScale + (maxScale - minScale) * 
                   (sin(scaleSpeed * currentTime) * 0.5f + 0.5f);
        }
        else {
            scale = 1.0f;  // �����ö���ʱʹ��Ĭ�ϴ�С
        }

        // Ӧ�����ź���ת
        float animAngle = 0.5f * currentTime;  // ������ת
        pyramidTransform.setRotation(0.0f, animAngle, 0.0f);  // ��Y����ת
        pyramidTransform.setScale(scale, scale, scale);  // ��������

        // ������ɫ������
        shader.SetUniformMat4fv("proj_matrix", projection);
        shader.SetUniformMat4fv("mv_matrix", view * pyramidTransform.getMatrix());
        
        // ���ݵ�ǰģʽѡ������
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

        // ����Ļ����ʾ��ǰ����ֵ��ʹ�õĹ���ģʽ
        // ����Ҫһ���ı���Ⱦϵͳ�����û�У�����ʡ���ⲿ��
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Draw3PyramidsWithTextureControls(GLFWwindow* window)
{
    // ����������ͬ����ģʽ������
    Texture textureNearest("res/textures/cheese.jpg", 
        TextureFilterMode::NEAREST,  // �������ˣ����ػ���
        TextureFilterMode::NEAREST,
        TextureWrapMode::REPEAT,
        TextureWrapMode::REPEAT);
        
    Texture textureLinear("res/textures/cheese.jpg", 
        TextureFilterMode::LINEAR,   // ���Թ��ˣ�ƽ����
        TextureFilterMode::LINEAR,
        TextureWrapMode::REPEAT,
        TextureWrapMode::REPEAT);
        
    Texture textureMipmap("res/textures/cheese.jpg", 
        TextureFilterMode::LINEAR, 
        TextureFilterMode::LINEAR_MIPMAP_LINEAR,  // �����Թ��ˣ����������
        TextureWrapMode::REPEAT,
        TextureWrapMode::REPEAT,
        true);  // ����mipmap

    Shader shader("res/shaders/3DShaderWithTexture.shader");
    Pyramid pyramid;

    // MVP����
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;

    // �������ʼ��
    Camera camera(
        glm::vec3(0, 1, 10),   // λ�õ���һ�㣬����ƶ��Ա㿴������������
        glm::vec3(0, 0, 0),    // Ŀ���
        glm::vec3(0, 1, 0),    // ������
        70.0f, aspect, 0.1f, 100.0f
    );

    // ������������Transform
    Transform pyramid1Transform;
    Transform pyramid2Transform;
    Transform pyramid3Transform;
    
    // ��ʼ����λ�ã�ˮƽ���У�
    pyramid1Transform.setPosition(-4.0f, 0.0f, -10.0f);  // ���
    pyramid2Transform.setPosition(0.0f, 0.0f, -10.0f);   // �м�
    pyramid3Transform.setPosition(4.0f, 0.0f, -10.0f);   // �ұ�
    
    // Ӧ��һЩ��ʼ��ת��ʹ���ǿ�������ͬ
    pyramid1Transform.setRotation(10.0f, 0.0f, 0.0f);     // ��׼����
    pyramid2Transform.setRotation(10.0f, 0.0f, 0.0f);    // Y����ת45��
    pyramid3Transform.setRotation(10.0f, 0.0f, 0.0f);   // Y����ת-45��

    glm::mat4 view = camera.GetViewMatrix();              // ��ͼ����
    glm::mat4 projection = camera.GetProjectionMatrix();  // ͶӰ����

    Renderer renderer;
    renderer.SetPolygonMode(false).SetDepthTest(true);    // ������Ȳ���

    // ������Ʋ���
    float moveSpeed = 0.4f;          // �ƶ��ٶ�
    float rotationSpeed = 0.05f;      // ��ת�ٶ�
    
    // ��Ϣ��ʾ
    glfwSetWindowTitle(window, "3 Pyramids Demo | ��[W/S]�����ƾ��� | ��[A/D]��������ת");
    
    // ��ѭ��
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        float currentTime = static_cast<float>(glfwGetTime());
        
        // �������봦�� - ���ƽ������ľ���
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            // W�� - ����������
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
            // S�� - ��Զ������
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
        
        // ��ת����
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            // A�� - ��ʱ����ת
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
            // D�� - ˳ʱ����ת
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
        
        // ���㵱ǰZλ�ã����´��ڱ�����ʾ��Ϣ
        std::string zPosStr = "Zλ��: " + std::to_string(pyramid2Transform.getPosition().z);
        glfwSetWindowTitle(window, ("3 Pyramids Demo | W/S���ƾ��� | A/D������ת | " + zPosStr).c_str());

        // ������ɫ��ͶӰ���󣨶����н�������ͬ��
        shader.SetUniformMat4fv("proj_matrix", projection);
        
        // ��Ⱦ��һ�����������������ˣ�
        shader.SetUniformMat4fv("mv_matrix", view * pyramid1Transform.getMatrix());
        renderer.Draw(pyramid, shader, textureNearest);
        
        // ��Ⱦ�ڶ��������������Թ��ˣ�
        shader.SetUniformMat4fv("mv_matrix", view * pyramid2Transform.getMatrix());
        renderer.Draw(pyramid, shader, textureLinear);
        
        // ��Ⱦ��������������Mipmap���ˣ�
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


    // MVP����ͬ Cube
    int width, height;
    GLCall(glfwGetFramebufferSize(window, &width, &height));
    float aspect = (float)width / (float)height;

    // �������ʼ��
    Camera camera(
        glm::vec3(0, 0, 3), // position
        glm::vec3(0, 0, 0),  // target
        glm::vec3(0, 1, 0),  // up
        70.0f, aspect, 0.1f, 100.0f
    );


    // ��ʼ�������Transform
    Transform cubeTransform;
    cubeTransform.setPosition(0.0f, 0.0f, -5.0f); // ���������

    Transform pyramidTransform;
    pyramidTransform.setPosition(0.0f, -2.0f, -5.0f); // ������ƫ��

    glm::mat4 view = camera.GetViewMatrix();              //View Matrix
    glm::mat4 projection = camera.GetProjectionMatrix();  //Projection Matrix

    Renderer renderer;
    renderer.SetPolygonMode(false).SetDepthTest(true); //�����߿�ģʽ����Ȳ���

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        float currentTime = static_cast<float>(glfwGetTime());

        // ====== Cube���� ======
        glm::mat4 cubeMV = view * cubeTransform.getMatrix();

        // ��������ת + Բ���˶�
        float animAngle = 1.75f * currentTime;
        float animX = sin(0.35f * currentTime) * 2.0f;
        float animY = cos(0.52f * currentTime) * 2.0f;
        float animZ = sin(0.7f * currentTime) * 2.0f;

        // ����Transform����
        cubeTransform.setPosition(animX, animY, animZ - 5.0f);
        cubeTransform.setRotation(0.0f, animAngle, animAngle);

        //std::cout << camera.GetFrustumRectAtZ(-5) << std::endl;

        // --- ����shader & ����Cube ---
        shader.SetUniformMat4fv("mv_matrix", view * cubeTransform.getMatrix());
        shader.SetUniformMat4fv("proj_matrix", projection);

        renderer.Draw(cube, shader);

        // ====== Pyramid���� ======
        pyramidTransform.setRotation(animX, 0.0f, 0.0f);
        pyramidTransform.setScale(1.0f, 1.0f, 1.0f);


        shader.SetUniformMat4fv("mv_matrix", view * pyramidTransform.getMatrix());
        renderer.Draw(pyramid, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


}
