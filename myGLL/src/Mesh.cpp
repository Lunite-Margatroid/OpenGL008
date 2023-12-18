#include "render.h"
#include "Mesh.h"
// ��ʼ��
void Alpha::Mesh::SetupMesh()
{
	GLCall(glGenVertexArrays(1, &VAO));
	GLCall(glGenBuffers(1, &VBO));
	GLCall(glGenBuffers(1, &EBO));

	GLCall(glBindVertexArray(VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertice.size() * sizeof(Vertex),
		&vertice[0], GL_STATIC_DRAW));

	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice.size() * sizeof(unsigned int),
		&indice[0], GL_STATIC_DRAW));

	// ����λ��position
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0));

	// ������
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)));

	// ��������
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord)));
	
	GLCall(glBindVertexArray(0));
}

Alpha::Mesh::Mesh(std::vector<Vertex> vertice, std::vector<unsigned int> indice, std::vector<Texture> textures)
{
	this->vertice = vertice;
	this->indice = indice;
	this->textures = textures;

	SetupMesh();
}

void Alpha::Mesh::Draw(LM::Shader& shader)
{
	/* 
	shader������ͼ��������:
	struct Material
	{
		sampler2D texture_diffuse1;
		sampler2D texture_diffuse2;
		sampler2D texture_diffuse3;
		sampler2D texture_diffuse4;

		sampler2D texture_specular1;
		sampler2D texture_specular2;
		sampler2D texture_specular3;
		sampler2D texture_specular4;

		float shininess;
	};

	Material material;
	*/

	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		else
		{
			// __debugbreak();
			continue;
		}

		// ������ܳ���uniform�Ҳ���������
		// ������������Ƿ񳬹��˲�����
		shader.SetUniform1i("material." + name + number, i);
		GLCall(glBindTexture(GL_TEXTURE_2D, textures[i].id));
	}
		GLCall(glBindVertexArray(VAO));
		GLCall(glDrawElements(GL_TRIANGLES, indice.size(), GL_UNSIGNED_INT, 0));

		glBindVertexArray(0);
}
