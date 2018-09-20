
#include "mesh.hpp"
#include <glad/glad.h>

float tetHedData[] = {
	0.5f, -0.25f, 0.0f,
	-0.25f, -0.25f, 0.42f,
	-0.25f, -0.25f, -0.42f,
	0.0f, 0.5f, 0.0f
};

int indices[] = {
	0, 1, 2,
	0, 1, 3,
	1, 2, 3,
	2, 0, 3
};

Mesh* MeshLoader::Load(const std::string& name) {

	uint32_t VAO;
	uint32_t VBO;
	uint32_t EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tetHedData), tetHedData, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	return m_Meshes[name] = new Mesh{ GL_TRIANGLES, VBO, EBO, VAO, sizeof(tetHedData) };
}

void MeshLoader::Delete(Mesh* pMesh) {

	glDeleteBuffers(1, &pMesh->m_VBO);
	glDeleteBuffers(1, &pMesh->m_EBO);
	glDeleteVertexArrays(1, &pMesh->m_VAO);

	delete pMesh;
}

MeshLoader::MeshLoader() {}

MeshLoader::~MeshLoader() {

	for (auto& p : m_Meshes) {
		Delete(p.second);
	}
}

void MeshLoader::Unload(const std::string& name) {

	Delete(m_Meshes[name]);
	m_Meshes.erase(name);
}
