
#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP

#include <map>
#include <string>

#include <glad/glad.h>

struct Texture;

class TextureLoader {
	std::map<std::string, Texture*> m_Textures;

	void Delete(Texture* pTexture);

public:
	struct Params {
		GLint internalFormat = GL_RGBA;
		GLint format		 = GL_RGBA;
		GLint dataType		 = GL_UNSIGNED_BYTE; // Ignored on load.GL
		GLint magFilter		 = GL_LINEAR;
		GLint minFilter		 = GL_LINEAR_MIPMAP_LINEAR;
		GLint wrapS			 = GL_REPEAT;
		GLint wrapT			 = GL_REPEAT;
		bool  mipmapped		 = true;
	};

	Texture* Load(const std::string& name, const std::string& filename, Params params);
	Texture* Generate(const std::string& name, int height, int width, Params params);
	void	 Unload(const std::string& name);
	~TextureLoader();
};

struct Texture {
	const GLuint	id;
	const GLsizei   width;
	const GLsizei   height;
	const GLenum	target;
	const GLint		internalFormat;
	const GLint		format;
	const GLint		magFilter;
	const GLint		minFilter;
	const GLint		wrapS;
	const GLint		wrapT;
	const GLboolean mipmapped;

	void Bind(int unit = 0) {
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(target, id);
	}
};

#endif /* _TEXTURE_HPP */