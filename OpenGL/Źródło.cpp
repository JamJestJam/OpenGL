#include "Libs.h";

int main() {
	vec3(0.f);
	//glfwInit();
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		cout << "error";
	else
		cout << "its okey";
	return 0;
}