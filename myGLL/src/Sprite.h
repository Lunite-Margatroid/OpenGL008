#pragma once
#include "render.h"
#include "Shader.h"
namespace LM
{
	class Sprite
	{
	protected:
		// 顶点数组对象
		unsigned int m_vaoID;
		// 顶点缓冲对象
		unsigned int m_vboID;
		// element buffer object
		unsigned int m_eboID;
		// 图元类型
		GLenum m_eleType;
		// 图元个数
		int m_eleNum;
		// 是否采用drawelement
		bool m_bElement;
		// 坐标变换
		glm::vec3 m_Position;
		// 旋转变换
		// 四元数
		glm::vec4 m_Rotate;
		// scale变换
		glm::vec3 m_Scale;
		// 父节点
		Sprite* m_Parent;
		// 子节点
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