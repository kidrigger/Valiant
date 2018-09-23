#include "shader.hpp"
#include <glad/glad.h>
#include <sstream>
#include <vector>

// Shader constructor without geometry shader
Shader::Shader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragShaderPath) :
		m_Name(name) {

	std::string  vertexCode;
	std::string  fragmentCode;
	std::fstream vShaderFile;
	std::fstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	// Open files.
	try {
		vShaderFile.open(vertexShaderPath, std::ios::in);
		fShaderFile.open(fragShaderPath, std::ios::in);

		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode   = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	} catch (std::fstream::failure e) {
		throw std::runtime_error("SHADER_" + m_Name + "::" + std::string(e.what()));
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	GLint success;
	char  infoLog[512];

	// Compile Vertex Shader
	GLuint vShaderIdx = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShaderIdx, 1, &vShaderCode, nullptr);
	glCompileShader(vShaderIdx);

	glGetShaderiv(vShaderIdx, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vShaderIdx, 512, nullptr, infoLog);
		throw std::runtime_error("SHADER_" + m_Name + "::VERTEX_COMPILATION" + std::string(infoLog));
	}

	// Compile Fragment Shader
	GLuint fShaderIdx = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShaderIdx, 1, &fShaderCode, nullptr);
	glCompileShader(fShaderIdx);

	glGetShaderiv(fShaderIdx, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fShaderIdx, 512, nullptr, infoLog);
		throw std::runtime_error("SHADER_" + m_Name + "::FRAGMENT_COMPILATION::" + std::string(infoLog));
	}

	// Link the two.
	m_Shader = glCreateProgram();
	glAttachShader(m_Shader, vShaderIdx);
	glAttachShader(m_Shader, fShaderIdx);
	glLinkProgram(m_Shader);

	glGetProgramiv(m_Shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_Shader, 512, nullptr, infoLog);
		throw std::runtime_error("SHADER_" + m_Name + "::PROGRAM_LINKING::" + std::string(infoLog));
	}

	// Program made, clear out the shader objects.
	glDeleteShader(vShaderIdx);
	glDeleteShader(fShaderIdx);

	// Launch Introspection
	IntrospectShader();
}

// Shader constructor with geometry shader
Shader::Shader(const std::string& name, const std::string& vertexShaderPath, const std::string& geometryShaderPath, const std::string& fragShaderPath) :
		m_Name(name) {

	std::string  vertexCode;
	std::string  geometryCode;
	std::string  fragmentCode;
	std::fstream vShaderFile;
	std::fstream gShaderFile;
	std::fstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	// Open files.
	try {
		vShaderFile.open(vertexShaderPath, std::ios::in);
		gShaderFile.open(geometryShaderPath, std::ios::in);
		fShaderFile.open(fragShaderPath, std::ios::in);

		std::stringstream vShaderStream;
		std::stringstream gShaderStream;
		std::stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		gShaderStream << gShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		gShaderFile.close();
		fShaderFile.close();

		vertexCode   = vShaderStream.str();
		geometryCode = gShaderStream.str();
		fragmentCode = fShaderStream.str();
	} catch (std::fstream::failure e) {
		throw std::runtime_error("SHADER_" + m_Name + "::" + std::string(e.what()));
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* gShaderCode = geometryCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	GLint success;
	char  infoLog[512];

	// Compile Vertex Shaders
	GLuint vShaderIdx = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShaderIdx, 1, &vShaderCode, nullptr);
	glCompileShader(vShaderIdx);

	glGetShaderiv(vShaderIdx, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vShaderIdx, 512, nullptr, infoLog);
		throw std::runtime_error("SHADER_" + m_Name + "::VERTEX_COMPILATION::" + std::string(infoLog));
	}

	// Compile Geometry Shaders
	GLuint gShaderIdx = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(gShaderIdx, 1, &gShaderCode, nullptr);
	glCompileShader(gShaderIdx);

	glGetShaderiv(gShaderIdx, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(gShaderIdx, 512, nullptr, infoLog);
		throw std::runtime_error("SHADER_" + m_Name + "::GEOMETRY_COMPILATION::" + std::string(infoLog));
	}

	// Compile Fragment Shaders
	GLuint fShaderIdx = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShaderIdx, 1, &fShaderCode, nullptr);
	glCompileShader(fShaderIdx);

	glGetShaderiv(fShaderIdx, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fShaderIdx, 512, nullptr, infoLog);
		throw std::runtime_error("SHADER_" + m_Name + "::FRAGMENT_COMPILATION::" + std::string(infoLog));
	}

	// Link program
	m_Shader = glCreateProgram();
	glAttachShader(m_Shader, vShaderIdx);
	glAttachShader(m_Shader, gShaderIdx);
	glAttachShader(m_Shader, fShaderIdx);
	glLinkProgram(m_Shader);

	glGetProgramiv(m_Shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_Shader, 512, nullptr, infoLog);
		throw std::runtime_error("SHADER_" + m_Name + "::PROGRAM_LINKING::" + std::string(infoLog));
	}

	// Program linked, cleanup
	glDeleteShader(vShaderIdx);
	glDeleteShader(gShaderIdx);
	glDeleteShader(fShaderIdx);

	// Launch introspection.
	IntrospectShader();
}

// Destructor to delete the shader program
Shader::~Shader() {

	glDeleteProgram(m_Shader);
}

// Activates the shader
void Shader::Use() {

	glUseProgram(m_Shader);
}

// Introspection to get the active uniforms in the shader
void Shader::IntrospectShader() {

	GLint	 count;
	GLint	 size;
	GLint	 len;
	GLuint	type;
	const int NAME_MAX_LEN = 36;
	char	  name[NAME_MAX_LEN];

	glGetProgramiv(m_Shader, GL_ACTIVE_UNIFORMS, &count);
	m_Uniforms.resize(count);
	for (GLuint i = 0; i < count; i++) {
		glGetActiveUniform(m_Shader, i, NAME_MAX_LEN, &len, &size, &type, name);

		m_Uniforms[i] = {
			type,
			glGetUniformLocation(m_Shader, name),
			size,
			std::string(name)
		};
	}
}

// Check if particular uniform exists.
bool Shader::HasUniform(const std::string& name) const {
	for (const ShaderUniforms& unif : m_Uniforms) {
		if (unif.name == name) {
			return true;
		}
	}
	return false;
}

// Get location for uniform
GLuint Shader::GetUniformLocation(const std::string& name) const {
	for (const ShaderUniforms& unif : m_Uniforms) {
		if (unif.name == name) {
			return unif.location;
		}
	}
	return -1;
}

// Setters for each Uniform type
// -----------------------------
void Shader::SetBool(const std::string& name, bool value) {
	GLint loc = GetUniformLocation(name);
#ifndef NDEBUG
	if (loc < 0) {
		throw std::out_of_range("UNIF::" + name + "_DOES_NOT_EXIST");
	}
#endif
	glUniform1i(loc, (int)value);
}

// ----------------------------
void Shader::SetInt(const std::string& name, int value) {
	GLint loc = GetUniformLocation(name);
#ifndef NDEBUG
	if (loc < 0) {
		throw std::out_of_range("UNIF::" + name + "_DOES_NOT_EXIST");
	}
#endif
	glUniform1i(loc, value);
}

// ----------------------------
void Shader::SetFloat(const std::string& name, float value) {
	GLint loc = GetUniformLocation(name);
#ifndef NDEBUG
	if (loc < 0) {
		throw std::out_of_range("UNIF::" + name + "_DOES_NOT_EXIST");
	}
#endif
	glUniform1f(loc, value);
}

// ----------------------------
void Shader::SetMatrix(const std::string& name, const glm::mat2& value) {
	GLint loc = GetUniformLocation(name);
#ifndef NDEBUG
	if (loc < 0) {
		throw std::out_of_range("UNIF::" + name + "_DOES_NOT_EXIST");
	}
#endif
	glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

// ----------------------------
void Shader::SetMatrix(const std::string& name, const glm::mat3& value) {
	GLint loc = GetUniformLocation(name);
#ifndef NDEBUG
	if (loc < 0) {
		throw std::out_of_range("UNIF::" + name + "_DOES_NOT_EXIST");
	}
#endif
	glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

// ----------------------------
void Shader::SetMatrix(const std::string& name, const glm::mat4& value) {
	GLint loc = GetUniformLocation(name);
#ifndef NDEBUG
	if (loc < 0) {
		throw std::out_of_range("UNIF::" + name + "_DOES_NOT_EXIST");
	}
#endif
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

// ----------------------------
void Shader::SetVector(const std::string& name, const glm::vec2& value) {
	GLint loc = GetUniformLocation(name);
#ifndef NDEBUG
	if (loc < 0) {
		throw std::out_of_range("UNIF::" + name + "_DOES_NOT_EXIST");
	}
#endif
	glUniform2fv(loc, 1, glm::value_ptr(value));
}

// ----------------------------
void Shader::SetVector(const std::string& name, const glm::vec3& value) {
	GLint loc = GetUniformLocation(name);
#ifndef NDEBUG
	if (loc < 0) {
		throw std::out_of_range("UNIF::" + name + "_DOES_NOT_EXIST");
	}
#endif
	glUniform3fv(loc, 1, glm::value_ptr(value));
}

// ----------------------------
void Shader::SetVector(const std::string& name, const glm::vec4& value) {
	GLint loc = GetUniformLocation(name);
#ifndef NDEBUG
	if (loc < 0) {
		throw std::out_of_range("UNIF::" + name + "_DOES_NOT_EXIST");
	}
#endif
	glUniform4fv(loc, 1, glm::value_ptr(value));
}

// ----------------------------
#ifndef NDEBUG

#define CASE_RET(v) \
	case v:         \
		return #v

std::string EnumToString(GLenum type) {
	switch (type) {
		CASE_RET(GL_FLOAT);
		CASE_RET(GL_INT);
		CASE_RET(GL_BOOL);
		CASE_RET(GL_FLOAT_VEC2);
		CASE_RET(GL_FLOAT_VEC3);
		CASE_RET(GL_FLOAT_VEC4);
		CASE_RET(GL_FLOAT_MAT2);
		CASE_RET(GL_FLOAT_MAT3);
		CASE_RET(GL_FLOAT_MAT4);
		CASE_RET(GL_SAMPLER_1D);
		CASE_RET(GL_SAMPLER_2D);
		CASE_RET(GL_SAMPLER_3D);
		CASE_RET(GL_SAMPLER_CUBE);
		default: return "ERR";
	}
}

void Shader::PrintUniformData() const {
	std::cout << "Shader " + m_Name + ":\n";
	for (const auto& unif : m_Uniforms) {
		std::cout << '\t' << unif.name << " : " << EnumToString(unif.type) << std::endl;
	}
}
#endif

// Load Shader into the shader cache, and return a pointer.
Shader* ShaderLoader::Load(const std::string& name, const std::string& vertexShaderPath, const std::string& fragShaderPath) {
#ifndef NDEBUG
	if (m_Shaders.count(name)) {
		throw std::runtime_error("SHDR_LOAD::" + name + "_NOT_UNIQUE");
	}
#endif
	return m_Shaders[name] = new Shader(name, vertexShaderPath, fragShaderPath);
}

// Gets a loaded shader.
Shader* ShaderLoader::Get(const std::string& name) {
#ifndef NDEBUG
	try {
		return m_Shaders.at(name);
	} catch (const std::exception& e) {
		throw std::runtime_error("SHDR_LOAD::" + std::string(e.what()));
	}
#else
	return m_Shaders[name];
#endif
}

// Unloads a loaded shader
void ShaderLoader::Unload(const std::string& name) {
#ifndef NDEBUG
	try {
		delete m_Shaders.at(name);
	} catch (const std::exception& e) {
		throw std::runtime_error("SHDR_LOAD::" + std::string(e.what()));
	}
	m_Shaders.erase(name);
#else
	delete m_Shaders[name];
	m_Shaders.erase(name);
#endif
}

// ----------------------------
