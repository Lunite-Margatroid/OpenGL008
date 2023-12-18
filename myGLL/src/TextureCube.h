#pragma once

namespace LM
{
	class TextureCube
	{
	private:
		unsigned int m_texID;
		unsigned char m_texIndex;
		bool LoadTexture(unsigned int* texture, const std::vector<std::string>& path, 
			int texColorMode, int resColorMode, bool bGenerateMipmap);
		void TexParameter();
	public:
		/// <summary>
		/// ���캯��
		/// </summary>
		/// <param name="imgPath">����ͼƬ·��</param>
		/// <param name="index">�������� ��0��ʼ�����15</param>
		/// <param name="texColorMode">�������ɫģʽ��һ��ΪGL_RGB��GL_RGBA��</param>
		/// <param name="imgColorMode">ͼƬ��Դ����ɫģʽ��ͬ��</param>
		/// <param name="bGenerateMipmap">�Ƿ����ɶ༶��Զ����Ĭ��Ϊtrue</param>
		TextureCube(const std::vector<std::string>& imgPath, unsigned char index, int texColorMode,
			int imgColorMode, bool bGenerateMipmap = true);
		~TextureCube();

		void Bind();

		unsigned char GetIndex()const;
	};
}