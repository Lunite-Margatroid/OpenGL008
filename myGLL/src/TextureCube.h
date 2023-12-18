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
		/// 构造函数
		/// </summary>
		/// <param name="imgPath">纹理图片路径</param>
		/// <param name="index">纹理索引 从0开始，最大15</param>
		/// <param name="texColorMode">纹理的颜色模式，一般为GL_RGB或GL_RGBA。</param>
		/// <param name="imgColorMode">图片资源的颜色模式，同上</param>
		/// <param name="bGenerateMipmap">是否生成多级渐远纹理，默认为true</param>
		TextureCube(const std::vector<std::string>& imgPath, unsigned char index, int texColorMode,
			int imgColorMode, bool bGenerateMipmap = true);
		~TextureCube();

		void Bind();

		unsigned char GetIndex()const;
	};
}