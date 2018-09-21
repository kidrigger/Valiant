
#include "texture.hpp"
#include <glad/glad.h>

#include <stbi/stb_image.h>
#include <stdexcept>

Texture* TextureLoader::Load(const std::string& name, const std::string& filename, Params params) {

#ifndef NDEBUG
	if (m_Textures.count(name)) {
		throw std::runtime_error("TEX_LOAD::" + name + "_NOT_UNIQUE");
	}
#endif

	params.dataType = GL_UNSIGNED_BYTE;

	uint32_t textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	int32_t  width;
	int32_t  height;
	int32_t  nrChannels;
	uint8_t* data;

	data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

	if (data) {

		switch (nrChannels) {
			case 1: {
				params.format = params.internalFormat = GL_RED;
			}; break;
			case 3: {
				params.format = params.internalFormat = GL_RGB;
			}; break;
			case 4: {
				params.format = params.internalFormat = GL_RGBA;
			}; break;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, params.internalFormat, width, height, 0, params.format, params.dataType, data);
		if (params.mipmapped) {
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		stbi_image_free(data);
	} else {
		stbi_image_free(data);
		throw std::runtime_error("TEX::IMAGE_" + name + "_NOT_FOUND");
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrapT);

	return m_Textures[name] = new Texture{
		textureID,
		width, height, GL_TEXTURE_2D,
		params.format, params.internalFormat,
		params.magFilter, params.minFilter,
		params.wrapS, params.wrapT,
		params.mipmapped
	};
}

Texture* TextureLoader::Generate(const std::string& name, int height, int width, Params params) {

#ifndef NDEBUG
	if (m_Textures.count(name)) {
		throw std::runtime_error("TEX_LOAD::" + name + "_NOT_UNIQUE");
	}
#endif

	params.mipmapped = false;

	uint32_t textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, params.internalFormat, width, height, 0, params.format, params.dataType, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrapT);

	return m_Textures[name] = new Texture{
		textureID,
		width, height, GL_TEXTURE_2D,
		params.format, params.internalFormat,
		params.magFilter, params.minFilter,
		params.wrapS, params.wrapT,
		params.mipmapped
	};
}

void TextureLoader::Delete(Texture* pTexture) {

	glDeleteTextures(1, &pTexture->id);
	delete pTexture;
}

void TextureLoader::Unload(const std::string& name) {

	Delete(m_Textures[name]);
	m_Textures.erase(name);
}

TextureLoader::~TextureLoader() {

	for (auto& p : m_Textures) {
		Delete(p.second);
	}
	m_Textures.clear();
}