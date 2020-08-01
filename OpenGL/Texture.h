#pragma once

#include <iostream>
#include <string>
#include <SOIL2.h>
#include <glm.hpp>
#include <glew.h>

class Texture {
public:
	/// <summary>
	/// Create new texture
	/// </summary>
	/// <param name="textureName">Texture file name</param>
	/// <param name="texture_unit">Texture unit ID</param>
	/// <param name="type">Texture type for exp. GL_TEXTURE_2D</param>
	Texture(std::string textureName, GLenum type = GL_TEXTURE_2D);
	/// <summary>
	/// Remove texture
	/// </summary>
	~Texture();
	/// <summary>
	/// create new texture with the seme texture unit
	/// </summary>
	/// <param name="textureName">Texture file name</param>
	void LoadFromFile(std::string textureName);
	/// <summary>
	/// Get texture ID
	/// </summary>
	/// <returns>Texture ID</returns>
	GLuint GetID() const;
	/// <summary>
	/// Bind texture
	/// </summary>
	void Bind(const GLint textureUnit);
	/// <summary>
	/// unbind texture
	/// </summary>
	void UnBind();
private:
	/// <summary>
	/// Texture ID
	/// </summary>
	GLuint ID;
	/// <summary>
	/// Texture width
	/// </summary>
	int width;
	/// <summary>
	/// Texture Height
	/// </summary>
	int height;
	/// <summary>
	/// texture type
	/// </summary>
	unsigned int type;
};

