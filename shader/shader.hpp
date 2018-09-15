

#ifndef _SHADER_H_GUARD
#define _SHADER_H_GUARD

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Shader {
private:
	uint32_t m_Shader;

	void IntrospectShader();

public:
	Shader(const std::string& vertexShaderPath, const std::string& fragShaderPath);
	Shader(const std::string& vertexShaderPath, const std::string& geometryShaderPath, const std::string& fragShaderPath);
	~Shader();

	void	 Use();
	void	 SetBool(const std::string& name, bool value);
	void	 SetFloat(const std::string& name, float value);
	void	 SetInt(const std::string& name, int value);
	void	 SetVector(const std::string& name, glm::vec2 value);
	void	 SetVector(const std::string& name, glm::vec3 value);
	void	 SetVector(const std::string& name, glm::vec4 value);
	void	 SetVectorArray(const std::string& name, const std::vector<glm::vec2>& value);
	void	 SetVectorArray(const std::string& name, const std::vector<glm::vec3>& value);
	void	 SetVectorArray(const std::string& name, const std::vector<glm::vec4>& value);
	void	 SetMatrix4fv(const std::string& name, glm::mat4 value);
	void	 SetMatrix4fvArray(const std::string& name, const std::vector<glm::mat4>& value);
	uint32_t GetID() {
		return m_Shader;
	}
};

#endif /* _SHADER_H_GUARD */