#pragma once
namespace LM
{
	class FrameBuffer
	{
	private:
		unsigned int m_fboID;		// frame buffer object id
		unsigned int m_texID;		// texture id
		unsigned int m_rboID;		// render buffer object id
		unsigned char m_texIndex;
		int m_width;
		int m_height;
	public:
		FrameBuffer(int width, int height, unsigned char index=0);
		~FrameBuffer();
		void Bind();
		void Unbind();
		unsigned int GetTextureID() const;
		unsigned char GetTexIndex() const;
	};
}