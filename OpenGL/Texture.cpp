#include "Texture.h"

Texture::Texture(std::string textureName, GLint texture_unit, GLenum type) {
	//save data
	this->type = type;
	this->textureUnit = texture_unit;
	//image location
	std::string src = "./Images/" + textureName + ".png";
	//load image                        
	unsigned char* image = SOIL_load_image(src.c_str(), &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

	glGenTextures(1, &this->ID);//create space to texture
	glBindTexture(type, this->ID);//set buffer, type to texture 2D and use it

	//set options to texture
	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);//if texture is smaller then object, texture repet on width
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);//if texture is smaller then object, texture repet on height
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);//antyaliasing to the texture
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//antyaliasing to the texture

	if (!image)//if is not something in image
	{
		std::cout << "ERROR::TEXTURE::TEXTURE_LOAD_FAIL::" << src << std::endl;
	}
	else {
		//generate texture image
		glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(type);//generate texture in several difren resolutions
	}

	glActiveTexture(0);//unactivate texture
	glBindTexture(type, 0);//unbind texture
	SOIL_free_image_data(image);//remove image data from ram
}

Texture::~Texture() {
	glDeleteTextures(1, &this->ID);//delete texture
}

void Texture::LoadFromFile(std::string textureName) {
	if (this->ID)
		glDeleteTextures(1, &this->ID);

	//image location
	std::string src = "./Images/" + textureName + ".png";
	//load image                        
	unsigned char* image = SOIL_load_image(src.c_str(), &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

	glGenTextures(1, &this->ID);//create space to texture
	glBindTexture(this->type, this->ID);//set buffer, type to texture 2D and use it

	//set options to texture
	glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);//if texture is smaller then object, texture repet on width
	glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);//if texture is smaller then object, texture repet on height
	glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);//antyaliasing to the texture
	glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//antyaliasing to the texture

	if (!image)//if is not something in image
	{
		std::cout << "ERROR::TEXTURE::LOAD_FROM_FILE::TEXTURE_LOAD_FAIL::" << src << std::endl;
	}
	else {
		//generate texture image
		glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(this->type);//generate texture in several difren resolutions
	}

	glActiveTexture(0);//unactivate texture
	glBindTexture(this->type, 0);//unbind texture
	SOIL_free_image_data(image);//remove image data from ram
}

GLuint Texture::GetID() const {
	return this->ID;
}

GLuint Texture::GetTextureUnit() const {
	return this->textureUnit;
}

void Texture::Bind() {
	glActiveTexture(GL_TEXTURE0 + this->textureUnit);
	glBindTexture(this->type, this->ID);
}

void Texture::UnBind() {
	glActiveTexture(0);
	glBindTexture(this->type, 0);
}

