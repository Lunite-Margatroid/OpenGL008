#include "render.h"
#include "FrameBuffer.h"

LM::FrameBuffer::FrameBuffer(int width, int height, unsigned char index):m_width(width),m_height(height),m_texIndex(index)
{
	// ����֡�������
	GLCall(glGenFramebuffers(1, &m_fboID));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fboID));

	// �����������
	GLCall(glGenTextures(1, &m_texID));
	GLCall(glActiveTexture(GL_TEXTURE0 + m_texIndex));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texID));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_INT, NULL));

	// ���û��Ʒ�ʽ�Ͳ�ֵ��ʽ
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	// ������Ⱦ�������
	GLCall(glGenRenderbuffers(1, &m_rboID));
	GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_rboID));
	GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height));

	// ������������Ⱦ����
	GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texID, 0));
	GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboID));
	// ���������
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		__debugbreak();
	}
}

LM::FrameBuffer::~FrameBuffer()
{
	glDeleteTextures(1, &m_texID);
	glDeleteRenderbuffers(1, &m_rboID);
	glDeleteFramebuffers(1, &m_rboID);
}

void LM::FrameBuffer::Bind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_fboID));
}

void LM::FrameBuffer::Unbind()
{
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

unsigned int LM::FrameBuffer::GetTextureID() const
{
	return m_texID;
}

unsigned char LM::FrameBuffer::GetTexIndex() const
{
	GLCall(glActiveTexture(GL_TEXTURE0+m_texIndex));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_texID));
	return m_texIndex;
}
