#include "Material.h"

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->diffuseTex = diffuseTex;
	this->specularTex = specularTex;
}

Material::~Material() {

}

void Material::sendToShader(Shader& program) {
	//send data to shader
	program.SetValueVec3(this->ambient, "material.ambient");
	program.SetValueVec3(this->diffuse, "material.diffuse");
	program.SetValueVec3(this->specular, "material.specular");
	program.SetValue1i(this->diffuseTex, "material.diffuseTex");
	program.SetValue1i(this->specularTex, "material.specularTex");
}