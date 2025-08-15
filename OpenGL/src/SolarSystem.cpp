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

std::stack<Transform> transformStk;


void PushTransform(const Transform& transform)
{
	if(transformStk.empty())
	{
		transformStk.push(Transform()); //��Ϊ��ջ����������һ����λ����
	}
	transformStk.push(transformStk.top());
	transformStk.top() = transformStk.top() * transform;
}

void PopTransform()
{
	if(!transformStk.empty())
	{
		transformStk.pop();
	}
}

void ClearTransformStack()
{
	while(!transformStk.empty())
	{
		transformStk.pop();
	}
	transformStk.push(Transform()); // ȷ��ջ��ʼ����һ����λ����
}





int width, height = 0;
void displaySoloar(GLFWwindow* window,double currentTime)
{ 
	//=========================��ʼ��========================================
	GLCall(glfwGetFramebufferSize(window, &width, &height));
	Camera camera(
		glm::vec3(0, 0, 10),  // position
		glm::vec3(0, 0, 0),  // target
		glm::vec3(0, 1, 0),  // up
		70.0f, (float)width / (float)height, 0.1f, 100.0f
	);

	Shader shader("res/shaders/SoloarSystem.shader");
	Renderer renderer;

	//��Ⱦ����
	renderer.SetDepthTest(true).SetPolygonMode(false); // ������Ȳ���

	// ����ģ�Ϳռ����
	Cube Earth, Moon;
	Pyramid Sun;




	renderer.Clear();

	//==========================���ñ任����========================================

	//��ȡͶӰ����P
	Transform porjectionTransform = camera.GetProjectionMatrix();
	PushTransform(porjectionTransform);	//��ͶӰ����ѹ��ջ��

	//��ȡ��ͼ����V
	Transform viewTransform = camera.GetViewMatrix();
	PushTransform(viewTransform);

	//��������ռ�任
	Transform earthTransformPos, moonTransformPos, sunTransformPos;
	Transform earthTransformRotate, moonTransformRotate, sunTransformRotate;


	//----------------------------̫��------------------------------------------
	sunTransformPos.setPosition(0.0f, 0.0f, 0.0f);			//̫��λ��
	PushTransform(sunTransformPos);							//��̫��λ�ñ任����ѹ��ջ��

	sunTransformRotate.setRotation((float)currentTime, 0, 0);			//̫����ת
	PushTransform(sunTransformRotate);									//��̫������任����ѹ��ջ��

	shader.SetUniformMat4fv("mvp_matrix", transformStk.top().getMatrix());
	renderer.Draw(Sun, shader);
	PopTransform();	//����̫����ת


	//----------------------------����------------------------------------------
	earthTransformPos.setPosition(sin((float)currentTime) *8.0, 0.0f, cos((float)currentTime)*4.0);	//����λ��
	PushTransform(earthTransformPos);	//������λ�ñ任����ѹ��ջ��

	earthTransformRotate.setRotation(0.0f, (float)currentTime, 0.0f);	//������ת
	earthTransformRotate.setScale(0.5f, 0.5f, 0.5f);					//��Ӱ�������ת������
	PushTransform(earthTransformRotate);	//����������任����ѹ��ջ��

	shader.SetUniformMat4fv("mvp_matrix", transformStk.top().getMatrix());
	renderer.Draw(Earth, shader);
	PopTransform();	//����������ת


	//----------------------------����------------------------------------------
	moonTransformPos.setPosition(0 , sin((float)currentTime)*1.0, cos((float)currentTime) * 1.0f);	//����λ��
	PushTransform(moonTransformPos);	//������λ�ñ任����ѹ��ջ��

	moonTransformRotate.setRotation(0.0f, (float)currentTime, 0.0f);	//������ת
	moonTransformRotate.setScale(0.2f, 0.2f, 0.2f);					//��Ӱ��������ת������
	PushTransform(moonTransformRotate);	//����������任����ѹ��ջ��

	shader.SetUniformMat4fv("mvp_matrix", transformStk.top().getMatrix());
	renderer.Draw(Moon, shader);

	ClearTransformStack();	//��ձ任ջ��׼����һ������ı任


}