#pragma once

#include "Shader.h"

class Material
{
public:
	/// <summary>
	/// create new material
	/// </summary>
	/// <param name="ambient">How mate shines</param>
	/// <param name="diffuse">How object reflects light</param>
	/// <param name="specular">How object leaves dew</param>
	/// <param name="diffuseTex">First texture unit</param>
	/// <param name="specularTex">Secound texture unit</param>
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex);
	/// <summary>
	/// remove material
	/// </summary>
	~Material();
	/// <summary>
	/// Send data to program
	/// </summary>
	/// <param name="program">shader</param>
	void sendToShader(Shader& program);
private:
	//material options
	/// <summary>
	/// How mate shines
	/// </summary>
	glm::vec3 ambient;
	/// <summary>
	/// How object reflects light
	/// </summary>
	glm::vec3 diffuse;
	/// <summary>
	/// How object leaves dew
	/// </summary>
	glm::vec3 specular;
	/// <summary>
	/// material main texture
	/// </summary>
	GLint diffuseTex;
	/// <summary>
	/// material secound texture
	/// </summary>
	GLint specularTex;
};

