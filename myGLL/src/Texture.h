#pragma once

namespace LM
{
	class Texture
	{
	protected:
		unsigned int m_uTextureID;
		unsigned char m_ubTextureIndex;

		/// <summary>
		/// ��������
		/// </summary>
		/// <param name="texture">�������id</param>
		/// <param name="path">����ͼƬԴ�ļ�</param>
		/// <param name="index">��������</param>
		/// <param name= "texColorMode">������ɫģʽ</param>
		/// <param name= "resColorMode">ԴͼƬ��ɫģʽ</param>
		/// <param name="bGenerateMipmap">�Ƿ��Զ����ɶ༶��Զ����</param>
		/// <returns></returns>
		virtual bool LoadTexture(unsigned int* texture, const std::string& path, unsigned char index,
			int texColorMode, int resColorMode, bool bGenerateMipmap);
	public:
		/// <summary>
		/// ���캯��
		/// </summary>
		/// <param name="imgPath">����ͼƬ·��</param>
		/// <param name="index">�������� ��0��ʼ�����15</param>
		/// <param name="texColorMode">�������ɫģʽ��һ��ΪGL_RGB��GL_RGBA��</param>
		/// <param name="imgColorMode">ͼƬ��Դ����ɫģʽ��ͬ��</param>
		/// <param name="bGenerateMipmap">�Ƿ����ɶ༶��Զ����Ĭ��Ϊtrue</param>
		Texture(const std::string& imgPath, unsigned char index, int texColorMode,
			int imgColorMode, bool bGenerateMipmap = true);
		~Texture();
		Texture() {};


		virtual void Bind();

		virtual unsigned char GetIndex()const;

	};
}

