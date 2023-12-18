#include "render.h"
#include "Texture.h"
namespace LM
{

	bool Texture::LoadTexture(unsigned int* texture, const std::string& path, unsigned char index, int texColorMode, int resColorMode, bool bGenerateMipmap)
	{
		int width, height, nChannals;
		unsigned char* img_data;
		img_data = stbi_load(path.c_str(), &width, &height, &nChannals, 0);

		if (img_data == 0)
		{
			std::cout << "Fail to load img!----" << path << std::endl;
			return false;
		}
		GLCall(glGenTextures(1, texture));
		GLCall(glActiveTexture(GL_TEXTURE0 + index));
		GLCall(glBindTexture(GL_TEXTURE_2D, *texture)); // ������


		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, texColorMode, width, height, 0, resColorMode, GL_UNSIGNED_BYTE, img_data));
		// param1 ����Target
		// param2 �༶��Զ���� 0Ϊ��������
		// param3 �����ʽ
		// param4&5 ��Ⱥ͸߶�x&y
		// param6 ��ʷ���� ��Ϊ0
		// param7 Դ���ݸ�ʽ
		// param8 Դ��������
		// param9 Դ����

		if (bGenerateMipmap)
			GLCall(glGenerateMipmap(GL_TEXTURE_2D));	// �Զ����ɶ༶��Զ��������
		stbi_image_free(img_data);						// �ͷ�ͼ����Դ
		return true;
	}

	Texture::Texture(const std::string& imgPath, unsigned char index, int texColorMode, int imgColorMode, bool bGenerateMipmap)
	{
		this->LoadTexture(&m_uTextureID, imgPath, index, texColorMode, imgColorMode, true);
		m_ubTextureIndex = index;
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));		// ���û��Ʒ�ʽ

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));	// ���ò�ֵ��ʽ
	}

	Texture::~Texture()
	{
		GLCall(glDeleteTextures(1, &m_uTextureID));
	}

	void Texture::Bind()
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + m_ubTextureIndex));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_uTextureID));
	}

	unsigned char Texture::GetIndex() const
	{
		return m_ubTextureIndex;
	}
}