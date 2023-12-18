#include "UniformBuffer.h"


LM::UniformBuffer::UniformBuffer(int size, void* data) :m_nSize(size)
{
	GLCall(glGenBuffers(1, &m_uboID));
	Bind();
	GLCall(glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW));
}

LM::UniformBuffer::~UniformBuffer()
{
	GLCall(glDeleteBuffers(1, &m_uboID));
}

inline void LM::UniformBuffer::Bind()
{
	GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_uboID));
}

int LM::UniformBuffer::WriteBuffer(int size,const void* data)
{
	Bind();
	if (size == m_nSize)
	{
		GLCall(glBufferData(GL_UNIFORM_BUFFER, size, data, GL_STATIC_DRAW));
		return size;
	}
	else if (size < m_nSize)
	{
		return SubWriteBuffer(0, size, data);
	}
	else if (size > m_nSize)
	{
		GLCall(glBufferData(GL_UNIFORM_BUFFER, m_nSize, data, GL_STATIC_DRAW));
		return m_nSize;
	}
	return 0;
}

int LM::UniformBuffer::SubWriteBuffer(int offset, int size, const void* data)
{
	Bind();
	if (offset + size <= m_nSize)
	{
		GLCall(glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data));
		return size;
	}
	else if(offset + size > m_nSize && offset < m_nSize)
	{
		GLCall(glBufferSubData(GL_UNIFORM_BUFFER, offset, m_nSize - offset, data));
		return m_nSize - offset;
	}
	return 0;
}

int LM::UniformBuffer::BindBufferBase(int bindingNode)
{
	Bind();
	GLCall(glBindBufferBase(GL_UNIFORM_BUFFER, bindingNode, m_uboID));
	return m_nSize;
}

int LM::UniformBuffer::BindBufferRange(int bindingNode, int offset, int size)
{
	if (offset + size < m_nSize)
	{
		GLCall(glBindBufferRange(GL_UNIFORM_BUFFER, bindingNode, m_uboID, offset, size));
		return size;
	}
	else if (offset + size > m_nSize && offset < m_nSize)
	{
		GLCall(glBindBufferRange(GL_UNIFORM_BUFFER, bindingNode, m_uboID, offset, m_nSize - offset));
		return m_nSize - offset;
	}
	return 0;
}
