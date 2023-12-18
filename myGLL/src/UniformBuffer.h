#pragma once
#include "render.h"

namespace LM
{
	class UniformBuffer
	{
	private:
		// 当前对象的ID
		unsigned int m_uboID;
		// 对象管理缓冲区的字节大小
		int m_nSize;
	public:
		/// <summary>
		/// 构造函数
		/// </summary>
		/// <param name="size"> 为缓冲配的字节大小</param>
		/// <param name="data"> 源数据的指针</param>
		UniformBuffer(int size, void* data = NULL);

		~UniformBuffer();
		/// <summary>
		/// 将当前对象绑定到GL_UNIFORM_BUFFER
		/// </summary>
		inline void Bind();

		/// <summary>
		/// 向缓冲区写入数据
		/// </summary>
		/// <param name="size">数据字节大小</param>
		/// <param name="data">数据头字节指针</param>
		/// <returns>返回实际写入的字节大小</returns>
		int WriteBuffer(int size, const void* data);

		/// <summary>
		/// 向缓冲区写入数据
		/// </summary>
		/// <param name="offset">相对于缓冲区头字节的偏移</param>
		/// <param name="size">写入字节的大小</param>
		/// <param name="data">源数据的头指针</param>
		/// <returns>返回实际写入的字节大小</returns>
		int SubWriteBuffer(int offset, int size, const void* data);

		/// <summary>
		/// 将当前对象绑定到指定节点
		/// </summary>
		/// <param name="bindingNode">节点索引</param>
		/// <returns>返回实际绑定的字节大小</returns>
		int BindBufferBase(int bindingNode);

		/// <summary>
		/// 将当前缓冲区的部分数据绑定到指定节点
		/// </summary>
		/// <param name="bindingNode">节点索引</param>
		/// <param name="offset">起始点相对于缓冲区头字节的偏移</param>
		/// <param name="size">绑定数据的字节大小</param>
		/// <returns>返回实际绑定的字节大小</returns>
		int BindBufferRange(int bindingNode, int offset, int size);
	};
}