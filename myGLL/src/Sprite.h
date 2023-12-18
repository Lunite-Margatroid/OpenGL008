#pragma once
#include "render.h"
#include "Shader.h"
namespace LM
{
	class Sprite
	{
	protected:
		// �����������
		unsigned int m_vaoID;
		// ���㻺�����
		unsigned int m_vboID;
		// element buffer object
		unsigned int m_eboID;
		// ͼԪ����
		GLenum m_eleType;
		// ͼԪ����
		int m_eleNum;
		// �Ƿ����drawelement
		bool m_bElement;
		// ����任
		glm::vec3 m_Position;
		// ��ת�任
		// ��Ԫ��
		glm::vec4 m_Rotate;
		// scale�任
		glm::vec3 m_Scale;
		// ���ڵ�
		Sprite* m_Parent;
		// �ӽڵ�
		std::vector<Sprite*> m_aChild;
		// Shader
		Shader* m_ptrShader;
	public:
		Sprite(Sprite* parent);
		~Sprite();

		void Draw();
		void DrawArray();
		void DrawElement();
	};
}