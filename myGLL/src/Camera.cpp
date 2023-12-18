#include "render.h"

#include "Camera.h"

namespace LM
{
	glm::mat4 Camera::GetViewTrans()
	{
		UpdateViewTrans();
		return glm::lookAt(m_position, m_position + m_front, m_up);
	}

	glm::mat4 Camera::GetProjectionTrans()
	{
		return glm::perspective(m_fov, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	}

	glm::vec3 Camera::GetPosition() const
	{
		return m_position;
	}

	glm::vec3 Camera::GetDirection() const
	{
		return m_front;
	}

	void Camera::ProcessKeyInput(GLFWwindow* window, float deltaTime)
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
	}

	void Camera::ProcessMouse(GLFWwindow* window, double xpos, double ypos)
	{
		static bool firstMouse = true;
		static float lastX = WIDTH / 2;
		static float lastY = HEIGHT / 2;

		if (firstMouse)
		{
			firstMouse = false;
			lastX = xpos;
			lastY = ypos;
		}

		float offsetX = xpos - lastX;
		float offsetY = lastY - ypos;

		CameraRotate(offsetX, offsetY);

		lastX = xpos;
		lastY = ypos;
	}

	void Camera::ProcessScroll(float offsety)
	{
		m_fov -= offsety * m_scrollSensitivity;

		if (m_fov > PI / 4.0f)
			m_fov = PI / 4.0f;
		if (m_fov < 0.02f)
			m_fov = 0.02f;
	}

	void Camera::UpdateViewTrans()
	{
		static glm::vec3 front;
		front.x = cos(m_pitch) * cos(m_yaw);
		front.y = sin(m_pitch);
		front.z = cos(m_pitch) * sin(m_yaw);
		m_front = glm::normalize(front);
		m_right = glm::normalize(glm::cross(front, m_worldUp));
	}

	void Camera::UpdateProjectionTrans()
	{
	}

	void Camera::CameraMove(Camera_Movement moveDir, float deltaTime)
	{
		switch (moveDir)
		{
		case FRONT:
			m_position += glm::cross(m_worldUp, m_right) * deltaTime * m_moveSpeed;
			break;
		case BACK:
			m_position -= glm::cross(m_worldUp, m_right) * deltaTime * m_moveSpeed;
			break;
		case LEFT:
			m_position -= m_right * deltaTime * m_moveSpeed;
			break;
		case RIGHT:
			m_position += m_right * deltaTime * m_moveSpeed;
			break;
		case UP:
			m_position.y += deltaTime * m_moveSpeed;
			break;
		case DOWN:
			m_position.y -= deltaTime * m_moveSpeed;
			break;
		default:break;
		};
	}

	void Camera::CameraRotate(float yaw, float patch)
	{
		m_yaw += yaw * m_rotateSensitivity;
		m_pitch += patch * m_rotateSensitivity;

		if (m_pitch > 1.5f)
			m_pitch = 1.5f;
		if (m_pitch < -1.5f)
			m_pitch = -1.5f;
	}

	Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up,
		float yaw, float pitch, float fov) :
		m_position(position),
		m_front(front),
		m_up(up),
		m_yaw(yaw),
		m_pitch(pitch),
		m_fov(fov)
	{
		m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		m_moveSpeed = SPEED;
		m_scrollSensitivity = SCROLL_SENSITIVITY;
		m_rotateSensitivity = ROTATE_SENEITIVITY;

		UpdateViewTrans();
		UpdateProjectionTrans();
	}

	void Camera::SetMoveSpeed(float moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}

	void Camera::SetScrollSensitivity(float sensitivity)
	{
		m_scrollSensitivity = sensitivity;
	}

	void Camera::SetRotateSensitivity(float sensitivity)
	{
		m_rotateSensitivity = sensitivity;
	}

	void Camera::SetFov(float fov)
	{
		m_fov = fov;
	}
}