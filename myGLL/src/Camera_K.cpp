#include "Camera_K.h"

LM::Camera_K::Camera_K()
{
}

LM::Camera_K::~Camera_K()
{
}

void LM::Camera_K::ProcessKeyInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		CameraMove(LM::FRONT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		CameraMove(LM::BACK, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		CameraMove(LM::LEFT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		CameraMove(LM::RIGHT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		CameraMove(LM::UP, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		CameraMove(LM::DOWN, deltaTime);
	}

	float yaw = 0.0f, pitch = 0.0f;
	if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
	{
		yaw += 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
	{
		yaw -= 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
	{
		pitch += 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
	{
		pitch -= 1.0f;
	}
	CameraRotate(yaw, pitch);
}

void LM::Camera_K::ProcessMouse(GLFWwindow* window, double xpos, double ypos)
{
}
