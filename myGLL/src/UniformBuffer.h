#pragma once
#include "render.h"

namespace LM
{
	class UniformBuffer
	{
	private:
		// ��ǰ�����ID
		unsigned int m_uboID;
		// ��������������ֽڴ�С
		int m_nSize;
	public:
		/// <summary>
		/// ���캯��
		/// </summary>
		/// <param name="size"> Ϊ��������ֽڴ�С</param>
		/// <param name="data"> Դ���ݵ�ָ��</param>
		UniformBuffer(int size, void* data = NULL);

		~UniformBuffer();
		/// <summary>
		/// ����ǰ����󶨵�GL_UNIFORM_BUFFER
		/// </summary>
		inline void Bind();

		/// <summary>
		/// �򻺳���д������
		/// </summary>
		/// <param name="size">�����ֽڴ�С</param>
		/// <param name="data">����ͷ�ֽ�ָ��</param>
		/// <returns>����ʵ��д����ֽڴ�С</returns>
		int WriteBuffer(int size, const void* data);

		/// <summary>
		/// �򻺳���д������
		/// </summary>
		/// <param name="offset">����ڻ�����ͷ�ֽڵ�ƫ��</param>
		/// <param name="size">д���ֽڵĴ�С</param>
		/// <param name="data">Դ���ݵ�ͷָ��</param>
		/// <returns>����ʵ��д����ֽڴ�С</returns>
		int SubWriteBuffer(int offset, int size, const void* data);

		/// <summary>
		/// ����ǰ����󶨵�ָ���ڵ�
		/// </summary>
		/// <param name="bindingNode">�ڵ�����</param>
		/// <returns>����ʵ�ʰ󶨵��ֽڴ�С</returns>
		int BindBufferBase(int bindingNode);

		/// <summary>
		/// ����ǰ�������Ĳ������ݰ󶨵�ָ���ڵ�
		/// </summary>
		/// <param name="bindingNode">�ڵ�����</param>
		/// <param name="offset">��ʼ������ڻ�����ͷ�ֽڵ�ƫ��</param>
		/// <param name="size">�����ݵ��ֽڴ�С</param>
		/// <returns>����ʵ�ʰ󶨵��ֽڴ�С</returns>
		int BindBufferRange(int bindingNode, int offset, int size);
	};
}