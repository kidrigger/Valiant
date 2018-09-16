

#ifndef _SHADER_HPP
#define _SHADER_HPP

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <map>
#include <vector>

#include <glad/glad.h>

/*
 * Shader Uniforms struct
 * Contains data to note the name, type and location of each 
 * active uniform in the shader.
 */

struct ShaderUniforms {
	GLenum		type;
	GLint		location;
	std::string name;
};

/* Forward Declaration */
class ShaderLoader;

/*
 * Shader class
 * Wrapper over the GLSL Shader loading and uniform setting methods
 * in OpenGL.
 */

class Shader {
private:
	GLuint						m_Shader;
	std::string					m_Name;
	std::vector<ShaderUniforms> m_Uniforms;

	void   IntrospectShader();
	GLuint GetUniformLocation(const std::string& name) const;

	// Constructor / Loaders. Load the appropriate files and compile into a Shader Programme before launching introspection.
	Shader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragShaderPath);
	Shader(const std::string& name, const std::string& vertexShaderPath, const std::string& geometryShaderPath, const std::string& fragShaderPath);
	~Shader();

	friend class ShaderLoader;

public:
	// Activate shader for use.
	void Use();

	// Getters for info about the shader;
	GLuint			   GetID() const { return m_Shader; }
	const std::string& GetName() const { return m_Name; }
	bool			   HasUniform(const std::string& name) const;

	// Setters for all the uniforms.
	void SetBool(const std::string& name, bool value);
	void SetFloat(const std::string& name, float value);
	void SetInt(const std::string& name, int value);
	void SetVector(const std::string& name, const glm::vec2& value);
	void SetVector(const std::string& name, const glm::vec3& value);
	void SetVector(const std::string& name, const glm::vec4& value);
	void SetMatrix(const std::string& name, const glm::mat2& value);
	void SetMatrix(const std::string& name, const glm::mat3& value);
	void SetMatrix(const std::string& name, const glm::mat4& value);

#ifndef NDEBUG
	void PrintUniformData() const;
#endif
};

/*
 * Shader Loader class
 * Is able to load Shaders and caches the loaded shaders.
 */

class ShaderLoader {
	std::map<std::string, Shader*> m_Shaders;

public:
	Shader* Load(const std::string& name, const std::string& vertexShaderPath, const std::string& fragShaderPath);
	Shader* Get(const std::string& name);
	void	Unload(const std::string& name);

	ShaderLoader() {}
	~ShaderLoader() {
		for (auto& p : m_Shaders) {
			delete p.second;
		}
	}
};

#endif /* _SHADER_HPP */