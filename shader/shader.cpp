#include "m_Shader.hpp"
#include <glad/glad.h>
#include <sstream>
#include <vector>

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragShaderPath) {

	std::string  vertexCode;
	std::string  fragmentCode;
	std::fstream vShaderFile;
	std::fstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
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
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	int32_t success;
	char	infoLog[512];

	uint32_t vShaderIdx = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShaderIdx, 1, &vShaderCode, nullptr);
	glCompileShader(vShaderIdx);

	glGetShaderiv(vShaderIdx, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vShaderIdx, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX_SHADER_COMPILATION_ERROR\n"
				  << infoLog << std::endl;
	}

	uint32_t fShaderIdx = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShaderIdx, 1, &fShaderCode, nullptr);
	glCompileShader(fShaderIdx);

	glGetShaderiv(fShaderIdx, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fShaderIdx, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT_SHADER_COMPILATION_ERROR\n"
				  << infoLog << std::endl;
	}

	m_Shader = glCreateProgram();
	glAttachShader(m_Shader, vShaderIdx);
	glAttachShader(m_Shader, fShaderIdx);
	glLinkProgram(m_Shader);

	glGetProgramiv(m_Shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_Shader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::SHADER_PROGRAM_LINKING_ERROR\n"
				  << infoLog << std::endl;
	}

	glDeleteShader(vShaderIdx);
	glDeleteShader(fShaderIdx);
}

Shader::Shader(const std::string& vertexShaderPath, const std::string& geometryShaderPath, const std::string& fragShaderPath) {

	std::string  vertexCode;
	std::string  geometryCode;
	std::string  fragmentCode;
	std::fstream vShaderFile;
	std::fstream gShaderFile;
	std::fstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
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
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* gShaderCode = geometryCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	int32_t success;
	char	infoLog[512];

	uint32_t vShaderIdx = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShaderIdx, 1, &vShaderCode, nullptr);
	glCompileShader(vShaderIdx);

	glGetShaderiv(vShaderIdx, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vShaderIdx, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX_SHADER_COMPILATION_ERROR\n"
				  << infoLog << std::endl;
	}

	uint32_t gShaderIdx = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(gShaderIdx, 1, &gShaderCode, nullptr);
	glCompileShader(gShaderIdx);

	glGetShaderiv(gShaderIdx, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(gShaderIdx, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::GEOMETRY_SHADER_COMPILATION_ERROR\n"
				  << infoLog << std::endl;
	}

	uint32_t fShaderIdx = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShaderIdx, 1, &fShaderCode, nullptr);
	glCompileShader(fShaderIdx);

	glGetShaderiv(fShaderIdx, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fShaderIdx, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT_SHADER_COMPILATION_ERROR\n"
				  << infoLog << std::endl;
	}

	m_Shader = glCreateProgram();
	glAttachShader(m_Shader, vShaderIdx);
	glAttachShader(m_Shader, gShaderIdx);
	glAttachShader(m_Shader, fShaderIdx);
	glLinkProgram(m_Shader);

	glGetProgramiv(m_Shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_Shader, 512, nullptr, infoLog);
		std::cerr << "ERROR::SHADER::SHADER_PROGRAM_LINKING_ERROR\n"
				  << infoLog << std::endl;
	}

	glDeleteShader(vShaderIdx);
	glDeleteShader(gShaderIdx);
	glDeleteShader(fShaderIdx);
}

Shader::~Shader() {
	glDeleteProgram(m_Shader);
}

void Shader::use() {
	glUseProgram(m_Shader);
}

void Shader::SetBool(const std::string& name, bool value) {
	glUniform1i(glGetUniformLocation(m_Shader, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(m_Shader, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(m_Shader, name.c_str()), value);
}

void Shader::SetMatrix4fv(const std::string& name, glm::mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(m_Shader, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMatrix4fvArray(const std::string& name, const std::vector<glm::mat4>& value) {
	int i = 0;
	for (auto val : value) {
		glUniformMatrix4fv(glGetUniformLocation(m_Shader, (name + "[" + std::to_string(i++) + "]").c_str()), 1, GL_FALSE, glm::value_ptr(val));
	}
}

void Shader::SetVector(const std::string& name, glm::vec2 value) {
	glUniform2fv(glGetUniformLocation(m_Shader, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetVector(const std::string& name, glm::vec3 value) {
	glUniform3fv(glGetUniformLocation(m_Shader, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetVector(const std::string& name, glm::vec4 value) {
	glUniform4fv(glGetUniformLocation(m_Shader, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetVectorArray(const std::string& name, const std::vector<glm::vec2>& value) {
	int i = 0;
	for (auto val : value) {
		glUniform4fv(glGetUniformLocation(m_Shader, (name + "[" + std::to_string(i++) + "]").c_str()), 1, glm::value_ptr(val));
	}
}

void Shader::SetVectorArray(const std::string& name, const std::vector<glm::vec3>& value) {
	int i = 0;
	for (auto val : value) {
		glUniform4fv(glGetUniformLocation(m_Shader, (name + "[" + std::to_string(i++) + "]").c_str()), 1, glm::value_ptr(val));
	}
}

void Shader::SetVectorArray(const std::string& name, const std::vector<glm::vec4>& value) {
	int i = 0;
	for (auto val : value) {
		glUniform4fv(glGetUniformLocation(m_Shader, (name + "[" + std::to_string(i++) + "]").c_str()), 1, glm::value_ptr(val));
	}
}
