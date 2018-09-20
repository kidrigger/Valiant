
#ifndef _MESH_HPP
#define _MESH_HPP

#include <stdint.h>
#include <map>
#include <string>

struct Mesh {

	const uint32_t m_Mode;
	const uint32_t m_VBO;
	const uint32_t m_EBO;
	const uint32_t m_VAO;
	const int32_t  m_Count; // Number of indices
};

class MeshLoader {

	std::map<std::string, Mesh*> m_Meshes;

	void Delete(Mesh* pMesh);

public:
	Mesh* Load(const std::string& name);
	void  Unload(const std::string& name);

	MeshLoader();
	~MeshLoader();
};

#endif /* _MESH_HPP */