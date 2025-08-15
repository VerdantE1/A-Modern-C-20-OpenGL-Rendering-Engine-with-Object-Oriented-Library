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
		transformStk.push(Transform()); //若为空栈，则先推入一个单位矩阵
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
	transformStk.push(Transform()); // 确保栈中始终有一个单位矩阵
}





int width, height = 0;
void displaySoloar(GLFWwindow* window,double currentTime)
{ 
	//=========================初始化========================================
	GLCall(glfwGetFramebufferSize(window, &width, &height));
	Camera camera(
		glm::vec3(0, 0, 10),  // position
		glm::vec3(0, 0, 0),  // target
		glm::vec3(0, 1, 0),  // up
		70.0f, (float)width / (float)height, 0.1f, 100.0f
	);

	Shader shader("res/shaders/SoloarSystem.shader");
	Renderer renderer;

	//渲染设置
	renderer.SetDepthTest(true).SetPolygonMode(false); // 启用深度测试

	// 创建模型空间对象
	Cube Earth, Moon;
	Pyramid Sun;




	renderer.Clear();

	//==========================设置变换矩阵========================================

	//获取投影矩阵P
	Transform porjectionTransform = camera.GetProjectionMatrix();
	PushTransform(porjectionTransform);	//将投影矩阵压入栈中

	//获取视图矩阵V
	Transform viewTransform = camera.GetViewMatrix();
	PushTransform(viewTransform);

	//设置世界空间变换
	Transform earthTransformPos, moonTransformPos, sunTransformPos;
	Transform earthTransformRotate, moonTransformRotate, sunTransformRotate;


	//----------------------------太阳------------------------------------------
	sunTransformPos.setPosition(0.0f, 0.0f, 0.0f);			//太阳位置
	PushTransform(sunTransformPos);							//将太阳位置变换矩阵压入栈中

	sunTransformRotate.setRotation((float)currentTime, 0, 0);			//太阳旋转
	PushTransform(sunTransformRotate);									//将太阳世界变换矩阵压入栈中

	shader.SetUniformMat4fv("mvp_matrix", transformStk.top().getMatrix());
	renderer.Draw(Sun, shader);
	PopTransform();	//弹出太阳自转


	//----------------------------地球------------------------------------------
	earthTransformPos.setPosition(sin((float)currentTime) *8.0, 0.0f, cos((float)currentTime)*4.0);	//地球位置
	PushTransform(earthTransformPos);	//将地球位置变换矩阵压入栈中

	earthTransformRotate.setRotation(0.0f, (float)currentTime, 0.0f);	//地球自转
	earthTransformRotate.setScale(0.5f, 0.5f, 0.5f);					//不影响地球自转的缩放
	PushTransform(earthTransformRotate);	//将地球世界变换矩阵压入栈中

	shader.SetUniformMat4fv("mvp_matrix", transformStk.top().getMatrix());
	renderer.Draw(Earth, shader);
	PopTransform();	//弹出地球自转


	//----------------------------月球------------------------------------------
	moonTransformPos.setPosition(0 , sin((float)currentTime)*1.0, cos((float)currentTime) * 1.0f);	//月球位置
	PushTransform(moonTransformPos);	//将月球位置变换矩阵压入栈中

	moonTransformRotate.setRotation(0.0f, (float)currentTime, 0.0f);	//月球自转
	moonTransformRotate.setScale(0.2f, 0.2f, 0.2f);					//不影响月球自转的缩放
	PushTransform(moonTransformRotate);	//将月球世界变换矩阵压入栈中

	shader.SetUniformMat4fv("mvp_matrix", transformStk.top().getMatrix());
	renderer.Draw(Moon, shader);

	ClearTransformStack();	//清空变换栈，准备下一个物体的变换


}