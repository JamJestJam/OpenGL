#include "Shader.h"

Shader::Shader(int GLmajorVer, int GLminorVer, const char* vertexName, const char* fragmentName, const char* geometryName ) {
	//load shaders
	GLuint vertexShader = this->LoadShader(GL_VERTEX_SHADER, vertexName, GLmajorVer, GLminorVer);
	GLuint geometryShader = (geometryName != "") ? this->LoadShader(GL_GEOMETRY_SHADER, geometryName, GLmajorVer, GLminorVer) : 0;
	GLuint fragmentShader = this->LoadShader(GL_FRAGMENT_SHADER, fragmentName, GLmajorVer, GLminorVer);

	//link program
	this->linkProgram(vertexShader, geometryShader, fragmentShader);

	//delete stuf
	glDeleteShader(vertexShader);//delete shader !important
	glDeleteShader(geometryShader);//delete shader !important
	glDeleteShader(fragmentShader);//delete shader !important
	//stop using program
}

Shader::~Shader() {
	glDeleteProgram(this->ID);//delete program from VRAM
}

std::string Shader::LoadShaderSource(const char* shaderName, int GLmajorVer, int GLminorVer) {
	std::string temp = "";//used to get line
	std::string src = "";//save data

	std::ifstream inFile;//fsteream

	//vertex shader
	inFile.open(".\\Shaders\\"+std::string(shaderName));//open file

	if (inFile.is_open()) {//check if file is open
		while (getline(inFile, temp)) {//read all lines
			src += temp + "\n";//add line to src
		}
	}
	else {//if is not open
		std::cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE::" << shaderName << std::endl;//show error
	}
	inFile.close();//close file

	std::string version = std::to_string(GLmajorVer) + std::to_string(GLminorVer) + "0";
	src.replace(src.find("#version"), 12, "#version " + version);

	return src;
}

GLuint Shader::LoadShader(GLenum type, const char* shaderName, int GLmajorVer, int GLminorVer) {

	char infoLog[512];//info about errors for example. program isn't able to link or a shader isn't able to compile etc.
	GLint success;//this will be used to determine if the shader has loaded correctly

	GLuint shader = glCreateShader(type);//create shader id;
	std::string src_src = this->LoadShaderSource(shaderName, GLmajorVer, GLminorVer);
	const GLchar* src = src_src.c_str();//create shader source

	glShaderSource(shader, 1, &src, NULL);//set shader source
	glCompileShader(shader);//compile vertex shader

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);//get compile status
	if (!success) {//error check
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_SHADER::" << shaderName << std::endl;//show error
		std::cout << infoLog << std::endl;//show shader log 
	}

	return shader;
}

void Shader::linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader) {
	char infoLog[512];//info about errors for example. program isn't able to link or a shader isn't able to compile etc.
	GLint success;//this will be used to determine if the shader has loaded correctly

	this->ID = glCreateProgram();//create program

	glAttachShader(this->ID, vertexShader);//attach shader
	if (geometryShader)//if geometry shader is loaded
		glAttachShader(this->ID, geometryShader);//attach shader
	glAttachShader(this->ID, fragmentShader);//attach shader
	glLinkProgram(this->ID);//connect everything together

	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);//get program status
	if (!success) {//if status is bad
		glGetProgramInfoLog(this->ID, 512, NULL, infoLog);//get error code
		std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << std::endl;//show error
		std::cout << infoLog << std::endl;//show program log 
	}
}

void Shader::Use() {
	glUseProgram(this->ID);
}

void Shader::UnUse() {
	glUseProgram(0);
}

void Shader::SetValueMat4(glm::mat4 value, const GLchar* name, GLboolean transpose) {
	this->Use();//use program

	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, transpose, glm::value_ptr(value));//set value

	this->UnUse();//stop using program
}

void Shader::SetValueMat3(glm::mat3 value, const GLchar* name, GLboolean transpose) {
	this->Use();//use program

	glUniformMatrix3fv(glGetUniformLocation(this->ID, name), 1, transpose, glm::value_ptr(value));//set value

	this->UnUse();//stop using program
}

void Shader::SetValueVec4(glm::fvec4 value, const GLchar* name) {
	this->Use();//use program

	glUniform4fv(glGetUniformLocation(this->ID, name), 1, glm::value_ptr(value));//set value

	this->UnUse();//stop using program
}

void Shader::SetValueVec3(glm::fvec3 value, const GLchar* name){
	this->Use();//use program

	glUniform3fv(glGetUniformLocation(this->ID, name), 1, glm::value_ptr(value));//set value

	this->UnUse();//stop using program
}

void Shader::SetValueVec2(glm::fvec2 value, const GLchar* name) {
	this->Use();//use program

	glUniform2fv(glGetUniformLocation(this->ID, name), 1, glm::value_ptr(value));//set value

	this->UnUse();//stop using program
}

void Shader::SetValue1f(GLfloat value, const GLchar* name) {
	this->Use();//use program

	glUniform1f(glGetUniformLocation(this->ID, name), value);//set value

	this->UnUse();//stop using program
}

void Shader::SetValue1i(GLint value, const GLchar* name) {
	this->Use();//use program

	glUniform1i(glGetUniformLocation(this->ID, name), value);//set value

	this->UnUse();//stop using program
}
