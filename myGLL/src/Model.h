#pragma once
#include "Mesh.h"
namespace Alpha
{
	class Model
	{
	private:
		void LoadModel(std::string path);
		std::vector<Mesh> meshes;
		std::string directory;
		std::vector<Texture> textures_loaded;
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name);
	public:
		Model(const char* path)
		{
			LoadModel(path);
		}
		void Draw(LM::Shader & shader);
	};
}