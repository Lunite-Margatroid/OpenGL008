#pragma once
#include <stb/stb_image.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <sstream>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdlib.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#define WIDTH	1600
#define HEIGHT	900

#ifndef PI
#define PI 3.14159f
#endif

// 命名空间Alpha
// opengl005项目新写的代码所用的namespace
// 在此之前的class写在namespace LM中
namespace Alpha
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoord;
	};

	struct Texture
	{
		unsigned int id;
		std::string type;
		aiString path;
	};
}
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

unsigned int TextureFromFile(const char* filename, const std::string &directory);