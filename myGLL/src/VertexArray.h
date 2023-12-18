#pragma once

namespace LM
{
	/// <summary>
	/// struct->AddBuffer->AddEle->PushAttrib->ApplyLayout->bindShader->draw
	/// </summary>
	class VertexArray
	{
	private:
		unsigned int m_VAO;	// Vertex Array Object
		unsigned int m_EBO;	// Element Buffer Object
		unsigned int m_VBO;	// Vertex Buffer Object
		int m_vertexCount;	// ������Ŀ ��������Ŀ
		GLenum m_eleType;
		std::vector<int> m_attribLayout;	// ÿ�����Ե�ά����Ŀ

		/// <summary>
	/// �������
	/// </summary>
	/// <param name="index">��������</param>
	/// <param name="nDimen">����ά��</param>
	/// <param name="stride">����</param>
	/// <param name="offset">ƫ��</param>
		void AddVertexAttrib(unsigned int index, int nDimen, int stride, int offset);

	public:
		VertexArray();
		~VertexArray();
		/// <summary>
		/// ��Ӷ���
		/// </summary>
		/// <param name="count">�������</param>
		/// <param name="nDimen">ÿ����������Ե�ά��</param>
		/// <param name="data">����ָ��</param>
		void AddBuffer(int count, int nDimen, const float* data);
		/// <summary>
		/// 
		/// </summary>
		/// <param name="count"> ������������Ŀ </param>
		/// <param name="data"></param>
		void AddElementBuffer(int count, const unsigned int* data);


		void DrawElement();
		void DrawArrays();
		void DrawArraysInstanced(int countInstance);
		void DrawElementInstanced(int countInstance);
		void Bind();
		void Unbind();

		void PushAttrib(int nDimen);
		void ClearAttrib();

		// Ӧ�õ�ǰ���Բ���
		void ApplyLayout();

		void SetElementType(GLenum eleType);
	};
}