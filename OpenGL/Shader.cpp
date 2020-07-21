#include "Shader.h"

Shader::Shader(const char* vertexName, const char* fragmentName, const char* geometryName ) {
	//load shaders
	GLuint vertexShader = this->LoadShader(GL_VERTEX_SHADER, vertexName);
	GLuint geometryShader = (geometryName != "") ? this->LoadShader(GL_GEOMETRY_SHADER, geometryName) : 0;
	GLuint fragmentShader = this->LoadShader(GL_FRAGMENT_SHADER, fragmentName);

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

string Shader::LoadShaderSource(const char* shaderName) {
	string temp = "";//used to get line
	string src = "";//save data

	ifstream inFile;//fsteream

	//vertex shader
	inFile.open(".\\Shaders\\"+string(shaderName));//open file

	if (inFile.is_open()) {//check if file is open
		while (getline(inFile, temp)) {//read all lines
			src += temp + "\n";//add line to src
		}
	}
	else {//if is not open
		cout << "ERROR::SHADER::COULD_NOT_OPEN_FILE::" << shaderName << endl;//show error
	}
	inFile.close();//close file

	return src;
}

GLuint Shader::LoadShader(GLenum type, const char* shaderName) {

	char infoLog[512];//info about errors for example. program isn't able to link or a shader isn't able to compile etc.
	GLint success;//this will be used to determine if the shader has loaded correctly

	GLuint shader = glCreateShader(type);//create shader id;
	string src_src = this->LoadShaderSource(shaderName);
	const GLchar* src = src_src.c_str();//create shader source
	glShaderSource(shader, 1, &src, NULL);//set shader source
	glCompileShader(shader);//compile vertex shader

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);//get compile status
	if (!success) {//error check
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cout << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_SHADER::" << shaderName << endl;//show error
		cout << infoLog << endl;//show shader log 
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
		cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << endl;//show error
		cout << infoLog << endl;//show program log 
	}
}

void Shader::Use() {
	glUseProgram(this->ID);
}

void Shader::UnUse() {
	glUseProgram(0);
}

void Shader::SetValueMat4(mat4 value, const GLchar* name, GLboolean transpose) {
	this->Use();//use program

	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, transpose, glm::value_ptr(value));//set value

	this->UnUse();//stop using program
}

void Shader::SetValueMat3(mat3 value, const GLchar* name, GLboolean transpose) {
	this->Use();//use program

	glUniformMatrix3fv(glGetUniformLocation(this->ID, name), 1, transpose, glm::value_ptr(value));//set value

	this->UnUse();//stop using program
}

void Shader::SetValueVec4(fvec4 value, const GLchar* name) {
	this->Use();//use program

	glUniform4fv(glGetUniformLocation(this->ID, name), 1, glm::value_ptr(value));//set value

	this->UnUse();//stop using program
}

void Shader::SetValueVec3(fvec3 value, const GLchar* name){
	this->Use();//use program

	glUniform3fv(glGetUniformLocation(this->ID, name), 1, glm::value_ptr(value));//set value

	this->UnUse();//stop using program
}

void Shader::SetValueVec2(fvec2 value, const GLchar* name) {
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
