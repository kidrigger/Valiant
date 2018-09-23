
#include "material.hpp"
#include <glad/glad.h>
#include <shader/shader.hpp>
#include <texture/texture.hpp>

void Material::SetBool(const std::string& name, bool value) {
	ShaderUniformValue suv;
	suv.type		 = GL_BOOL;
	suv.Bool		 = value;
	m_Uniforms[name] = suv;
}

void Material::SetFloat(const std::string& name, float value) {
	ShaderUniformValue suv;
	suv.type		 = GL_FLOAT;
	suv.Float		 = value;
	m_Uniforms[name] = suv;
}
void Material::SetInt(const std::string& name, int value) {
	ShaderUniformValue suv;
	suv.type		 = GL_INT;
	suv.Int			 = value;
	m_Uniforms[name] = suv;
}

void Material::SetVector(const std::string& name, const glm::vec2& value) {
	ShaderUniformValue suv;
	suv.type		 = GL_FLOAT_VEC2;
	suv.Vec2		 = value;
	m_Uniforms[name] = suv;
}

void Material::SetVector(const std::string& name, const glm::vec3& value) {
	ShaderUniformValue suv;
	suv.type		 = GL_FLOAT_VEC3;
	suv.Vec3		 = value;
	m_Uniforms[name] = suv;
}

void Material::SetVector(const std::string& name, const glm::vec4& value) {
	ShaderUniformValue suv;
	suv.type		 = GL_FLOAT_VEC4;
	suv.Vec4		 = value;
	m_Uniforms[name] = suv;
}

void Material::SetMatrix(const std::string& name, const glm::mat2& value) {
	ShaderUniformValue suv;
	suv.type		 = GL_FLOAT_MAT2;
	suv.Mat2		 = value;
	m_Uniforms[name] = suv;
}

void Material::SetMatrix(const std::string& name, const glm::mat3& value) {
	ShaderUniformValue suv;
	suv.type		 = GL_FLOAT_MAT3;
	suv.Mat3		 = value;
	m_Uniforms[name] = suv;
}

void Material::SetMatrix(const std::string& name, const glm::mat4& value) {
	ShaderUniformValue suv;
	suv.type		 = GL_FLOAT_MAT4;
	suv.Mat4		 = value;
	m_Uniforms[name] = suv;
}

void Material::SetTexture(const std::string& name, Texture* value, const uint32_t unit) {
	ShaderSamplerValue ssv;
	ssv.type		 = GL_SAMPLER_2D;
	ssv.unit		 = unit;
	ssv.Sampler2D	= value;
	m_Samplers[name] = ssv;
}

void Material::Attach(Shader* pShader) {
	if (!pShader) {
		pShader = m_Shader;
	}

#ifndef NDEBUG
	if (!m_Shader) {
		throw std::runtime_error("MATL::SHDR_NULL");
	}
#endif

	pShader->Use();

	for (const auto& p : m_Uniforms) {
		switch (p.second.type) {
			case GL_BOOL: {
				pShader->SetBool(p.first, p.second.Bool);
			}; break;
			case GL_INT: {
				pShader->SetInt(p.first, p.second.Int);
			}; break;
			case GL_FLOAT: {
				pShader->SetFloat(p.first, p.second.Float);
			}; break;
			case GL_FLOAT_VEC2: {
				pShader->SetVector(p.first, p.second.Vec2);
			}; break;
			case GL_FLOAT_VEC3: {
				pShader->SetVector(p.first, p.second.Vec3);
			}; break;
			case GL_FLOAT_VEC4: {
				pShader->SetVector(p.first, p.second.Vec4);
			}; break;
			case GL_FLOAT_MAT2: {
				pShader->SetMatrix(p.first, p.second.Mat2);
			}; break;
			case GL_FLOAT_MAT3: {
				pShader->SetMatrix(p.first, p.second.Mat3);
			}; break;
			case GL_FLOAT_MAT4: {
				pShader->SetMatrix(p.first, p.second.Mat4);
			}; break;
			default: {
				throw std::runtime_error("MATL::NO_SUCH_TYPE");
			}
		}
	}
	for (const auto& p : m_Samplers) {
		switch (p.second.type) {
			case GL_SAMPLER_2D: {
				p.second.Sampler2D->Bind(p.second.unit);
				pShader->SetInt(p.first, p.second.unit);
			}; break;
			default: {
				throw std::runtime_error("MATL::NO_SUCH_TYPE");
			}
		}
	}
}