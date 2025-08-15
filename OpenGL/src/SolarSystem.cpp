#include <stack>
#include "Transform.h"
#include "Camera.h"
#include "Utility.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "AllShaperTypes.h"
#include "Shader.h"
#include "Renderer.h"


class GLFWwindow; 

std::stack<Transform> transformstk;

int width, height = 0;



void displaySoloar(GLFWwindow* window,double currentTime)
{ 

	Shader shader("res/shaders/SoloarSystem.shader");
	Renderer renderer;

	GLCall(glfwGetFramebufferSize(window, &width, &height));
	Camera camera(
		glm::vec3(0, 0, 10),  // position
		glm::vec3(0, 0, 0),  // target
		glm::vec3(0, 1, 0),  // up
		70.0f, (float)width / (float)height, 0.1f, 100.0f
	);

	Transform viewTransform = camera.GetViewMatrix();				//��ȡ�۲����V
	Transform porjectionTransform = camera.GetProjectionMatrix();	//��ȡͶӰ����P




	// ����ģ�Ϳռ����
	Cube Earth, Moon;
	Pyramid Sun;


	// ��������任����
	Transform earthTransform,moonTransform,sunTransform;

	earthTransform.setPosition(0.0f, 0.0f, -5.0f);
	
	moonTransform.setPosition(0.0f, 3.0f, -5.0f);

	sunTransform.setPosition(-5.0f, 0.0f, -5.0f);

	renderer.SetDepthTest(true).SetPolygonMode(false); // ������Ȳ���
	//========================��Ⱦ=====================================================
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();
		//��Ⱦ����
		shader.SetUniformMat4fv("mv_matrix", (viewTransform * earthTransform).getMatrix());
		shader.SetUniformMat4fv("proj_matrix", porjectionTransform.getMatrix());
		renderer.Draw(Earth, shader);

		//��Ⱦ����
		shader.SetUniformMat4fv("mv_matrix", (viewTransform * moonTransform).getMatrix());
		shader.SetUniformMat4fv("proj_matrix", porjectionTransform.getMatrix());
		renderer.Draw(Moon, shader);

		//��Ⱦ̫��
		shader.SetUniformMat4fv("mv_matrix", (viewTransform * sunTransform).getMatrix());
		shader.SetUniformMat4fv("proj_matrix", porjectionTransform.getMatrix());
		renderer.Draw(Sun, shader);

		



		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	

}