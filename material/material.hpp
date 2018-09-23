
#ifndef _MATERIAL_HPP
#define _MATERIAL_HPP

#include <cstdint>
#include <map>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;
struct Texture;

struct ShaderUniformValue {
	uint32_t type;
	union {
		bool  Bool;
		int   Int;
		float Float;

		glm::vec2 Vec2;
		glm::vec3 Vec3;
		glm::vec4 Vec4;

		glm::mat2 Mat2;
		glm::mat3 Mat3;
		glm::mat4 Mat4;
	};

	ShaderUniformValue() {}
};

struct ShaderSamplerValue {
	uint32_t type;
	uint32_t unit;
	union {
		Texture* Sampler2D;
	};
};

class Material {
	Shader* m_Shader;

	std::map<std::string, ShaderUniformValue> m_Uniforms;
	std::map<std::string, ShaderSamplerValue> m_Samplers;

public:
	void Attach(Shader* pShader = nullptr);

	Shader* GetShader() { return m_Shader; }
	void	SetShader(Shader* pShader) { m_Shader = pShader; }

	void SetBool(const std::string& name, bool value);
	void SetFloat(const std::string& name, float value);
	void SetInt(const std::string& name, int value);
	void SetVector(const std::string& name, const glm::vec2& value);
	void SetVector(const std::string& name, const glm::vec3& value);
	void SetVector(const std::string& name, const glm::vec4& value);
	void SetMatrix(const std::string& name, const glm::mat2& value);
	void SetMatrix(const std::string& name, const glm::mat3& value);
	void SetMatrix(const std::string& name, const glm::mat4& value);
	void SetTexture(const std::string& name, Texture* value, const uint32_t unit = 0);

	const auto* GetUniforms() { return &m_Uniforms; }
	const auto* GetSamplers() { return &m_Samplers; }

	Material(Shader* pShader) :
			m_Shader(pShader) {
	}
};

#endif /* _MATERIAL_HPP */