#include "render.h"
#include "TextureCube.h"

bool LM::TextureCube::LoadTexture(unsigned int* texture, const std::vector<std::string>& path, int texColorMode, int resColorMode, bool bGenerateMipmap)
{
	int width, height, channels;
	for (int i = 0;i<path.size();i++)
	{
		// 顺序 右 左 上 下 后 前
		unsigned char* data = stbi_load(path[i].c_str(), &width, &height, &channels, 0);
		if (data)
		{
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, texColorMode, width, height, 0,
				resColorMode, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			std::cout << "fail to load image:" << path[i] << std::endl;
		}
		stbi_image_free(data);
	}

	return true;
}

void LM::TextureCube::TexParameter()
{
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP,	GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
}

LM::TextureCube::TextureCube(const std::vector<std::string>& imgPath, unsigned char index, int texColorMode, int imgColorMode, bool bGenerateMipmap)
{
	m_texIndex = index;
	glGenTextures(1, &m_texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID);

	this->LoadTexture(&m_texID, imgPath, texColorMode, imgColorMode, bGenerateMipmap);
	this->TexParameter();
}

LM::TextureCube::~TextureCube()
{
	GLCall(glDeleteTextures(1, &m_texID));
}

void LM::TextureCube::Bind()
{
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID));
}

unsigned char LM::TextureCube::GetIndex() const
{
	return m_texIndex;
}
