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
		纹理图片的路径包含中文
		模型文件记录的纹理数据的路径大概是用utf-8表示
		fopen不支持utf-8
		这里把utf-8转为宽字符 再用wfopen打开文件
		
		然而加载模型文件还是不支持中文路径 半吊子
	*/
	int width, height, nChannals;
	unsigned char* img_data = 0;
	unsigned int texture;

	GLCall(glGenTextures(1, &texture));
	// 获得纹理图片路径
	std::stringstream ss;
	ss << directory << "/" << filename;
	std::string path = ss.str();

	// utf-8转为宽字符
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
		
		GLCall(glBindTexture(GL_TEXTURE_2D, texture)); // 绑定纹理
	// param1 纹理Target
	// param2 多级渐远级别 0为基本级别
	// param3 纹理格式
	// param4&5 宽度和高度x&y
	// param6 历史遗留 恒为0
	// param7 源数据格式
	// param8 源数据类型
	// param9 源数据
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 
			0, format, GL_UNSIGNED_BYTE, img_data));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLCall(glGenerateMipmap(GL_TEXTURE_2D));	// 自动生成多级渐远级别纹理
		stbi_image_free(img_data);						// 释放图像资源
	}
	return texture;
}
