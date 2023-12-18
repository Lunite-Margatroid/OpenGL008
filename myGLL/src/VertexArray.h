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
		int m_vertexCount;	// 顶点数目 索引的数目
		GLenum m_eleType;
		std::vector<int> m_attribLayout;	// 每个属性的维度数目

		/// <summary>
	/// 添加属性
	/// </summary>
	/// <param name="index">属性索引</param>
	/// <param name="nDimen">属性维度</param>
	/// <param name="stride">步幅</param>
	/// <param name="offset">偏置</param>
		void AddVertexAttrib(unsigned int index, int nDimen, int stride, int offset);

	public:
		VertexArray();
		~VertexArray();
		/// <summary>
		/// 添加顶点
		/// </summary>
		/// <param name="count">顶点个数</param>
		/// <param name="nDimen">每个顶点的属性的维度</param>
		/// <param name="data">数据指针</param>
		void AddBuffer(int count, int nDimen, const float* data);
		/// <summary>
		/// 
		/// </summary>
		/// <param name="count"> 顶点索引的数目 </param>
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

		// 应用当前属性布局
		void ApplyLayout();

		void SetElementType(GLenum eleType);
	};
}