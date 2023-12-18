#pragma once
#include "render.h"
#include "Camera.h"
namespace LM
{
	/// <summary>
	/// 坐标移动键盘控制 欧拉角小键盘控制
	/// </summary>
	class Camera_K :public Camera
	{
	public:
		Camera_K();
		~Camera_K();
		void ProcessKeyInput(GLFWwindow* window, float deltaTime);
		void ProcessMouse(GLFWwindow* window, double xpos, double ypos);
	};

}