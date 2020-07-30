#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <glm.hpp>
#include <glew.h>
#include <glfw3.h>
#include <mat4x4.hpp>
#include <gtc/type_ptr.hpp>

class Shader
{
public:
	/// <summary>
	/// Shader init
	/// </summary>
	/// <param name="vertexName">vertex shader file name</param>
	/// <param name="geometryName">geometry shader file name</param>
	/// <param name="fragmentName">fragment shader file name</param>
	Shader(int GLmajorVer, int GLminorVer, const char* vertexName, const char* fragmentName, const char* geometryName = "");
	/// <summary>
	/// Shader destructor
	/// </summary>
	~Shader();
	/// <summary>
	/// Use program in openGL
	/// </summary>
	void Use();
	/// <summary>
	/// Stop using program in openGL
	/// </summary>
	void UnUse();
	/// <summary>
	/// Set openGL value
	/// </summary>
	/// <param name="value">value data</param>
	/// <param name="value">value name</param>
	/// <param name="transpose">transpose matrix</param>
	void SetValueMat4(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	/// <summary>
	/// Set openGL value
	/// </summary>
	/// <param name="value">value data</param>
	/// <param name="value">value name</param>
	/// <param name="transpose">transpose matrix</param>
	void SetValueMat3(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	/// <summary>
	/// Set openGL value
	/// </summary>
	/// <param name="value">value data</param>
	/// <param name="value">value name</param>
	void SetValueVec4(glm::fvec4 value, const GLchar* name);
	/// <summary>
	/// Set openGL value
	/// </summary>
	/// <param name="value">value data</param>
	/// <param name="value">value name</param>
	void SetValueVec3(glm::fvec3 value, const GLchar* name);
	/// <summary>
	/// Set openGL value
	/// </summary>
	/// <param name="value">value data</param>
	/// <param name="value">value name</param>
	void SetValueVec2(glm::fvec2 value, const GLchar* name);
	/// <summary>
	/// Set openGL value
	/// </summary>
	/// <param name="value">value data</param>
	/// <param name="value">value name</param>
	void SetValue1f(GLfloat value, const GLchar* name);
	/// <summary>
	/// Set openGL value
	/// </summary>
	/// <param name="value">value data</param>
	/// <param name="value">value name</param>
	void SetValue1i(GLint value, const GLchar* name);
private:
	/// <summary>
	/// Shader program id
	/// </summary>
	GLuint ID;
	/// <summary>
	/// Load source code from file
	/// </summary>
	/// <param name="shaderName">Shader file name</param>
	/// <returns>Shader code</returns>
	std::string LoadShaderSource(const char* shaderName, int GLmajorVer, int GLminorVer);
	/// <summary>
	/// Load shader from file
	/// </summary>
	/// <param name="type">Shader type ex. vertexShader, fragmentShader, geometryShader etc.</param>
	/// <param name="fileName">Shader file name</param>
	/// <returns></returns>
	GLuint LoadShader(GLenum type, const char* shaderName, int GLmajorVer, int GLminorVer);
	/// <summary>
	/// link shaders to program
	/// </summary>
	/// <param name="vertexShader">vertexShader</param>
	/// <param name="geometryShader">geometryShader</param>
	/// <param name="fragmentShader">fragmentShader</param>
	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);
};

