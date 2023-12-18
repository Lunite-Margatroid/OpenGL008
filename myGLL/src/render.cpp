#include "render.h"
#include <wchar.h>
#include <codecvt>
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " <<
			function << " file: " << file << "  line: " << line << std::endl;
		return false;
	}
	return true;
}

unsigned int TextureFromFile(const char* filename, const std::string& directory)
{
	/*
		����ͼƬ��·����������
		ģ���ļ���¼���������ݵ�·���������utf-8��ʾ
		fopen��֧��utf-8
		�����utf-8תΪ���ַ� ����wfopen���ļ�
		
		Ȼ������ģ���ļ����ǲ�֧������·�� �����
	*/
	int width, height, nChannals;
	unsigned char* img_data = 0;
	unsigned int texture;

	GLCall(glGenTextures(1, &texture));
	// �������ͼƬ·��
	std::stringstream ss;
	ss << directory << "/" << filename;
	std::string path = ss.str();

	// utf-8תΪ���ַ�
	std::wstring wstr;
	std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
	wstr = wcv.from_bytes(path);
	FILE* f;
	_wfopen_s(&f,wstr.c_str(), L"rb");
	if (f)
	{
		img_data = stbi_load_from_file(f, &width, &height, &nChannals, 0);
		fclose(f);
	}
	if (img_data == 0)
	{
		std::cout << "Fail to load img!" << std::endl;
		std::wcout << wstr << std::endl;
	}
	else
	{
		GLenum format;
		if (nChannals == 1)
			format = GL_RED;
		else if (nChannals == 3)
			format = GL_RGB;
		else if (nChannals == 4)
			format = GL_RGBA;
		
		GLCall(glBindTexture(GL_TEXTURE_2D, texture)); // ������
	// param1 ����Target
	// param2 �༶��Զ���� 0Ϊ��������
	// param3 �����ʽ
	// param4&5 ��Ⱥ͸߶�x&y
	// param6 ��ʷ���� ��Ϊ0
	// param7 Դ���ݸ�ʽ
	// param8 Դ��������
	// param9 Դ����
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 
			0, format, GL_UNSIGNED_BYTE, img_data));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLCall(glGenerateMipmap(GL_TEXTURE_2D));	// �Զ����ɶ༶��Զ��������
		stbi_image_free(img_data);						// �ͷ�ͼ����Դ
	}
	return texture;
}
