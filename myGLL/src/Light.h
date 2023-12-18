#pragma once
#include "Shader.h"

namespace LM
{
	class Light
	{
	protected:
		glm::vec3 m_v3Ambient;		// ������
		glm::vec3 m_v3Diffuse;		// ������
		glm::vec3 m_v3Specular;		// ���淴��
	public:
		virtual void SetUniformLight(const std::string& valueName, Shader& shader);
		void SetLightColor(glm::vec3 ambi, glm::vec3 diff, glm::vec3 spec);
		Light(glm::vec3 ambi, glm::vec3 diff, glm::vec3 spec);
		Light();
	};
}