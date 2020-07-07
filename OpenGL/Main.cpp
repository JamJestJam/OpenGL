#include "Libs.h"

void Framebuffer_resize_callback(GLFWwindow* win, int frameBufferWidth, int frameBufferHeight) {
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);
}

int main() {
	//init glfw
	glfwInit();//init glfw

	//create windows
	const int windowWidth = 640;//window width in px
	const int windowheight = 480;//window height in px
	const char* title = "Ucze sie";//window title

	//glfw setings
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//core version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//set version 4.4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);//don't allow windows resible

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowheight, title, NULL, NULL);//create new window

	glfwSetFramebufferSizeCallback(window, Framebuffer_resize_callback);//on window event "resize" callback function

	glfwMakeContextCurrent(window);//show window
	//init glew
	glewExperimental = GL_TRUE;//init glew

	if (glewInit() != GLEW_OK)//check if its okey
	{
		std::cout << "GLEW init fail\n";//show error in console
		glfwTerminate();//terminate glfw
		return 0;//shutdown program
	}
	
	glClearColor(1, 1, 1, 1);//set clear color to RGBA
	//main loop
	while (!glfwWindowShouldClose(window))//while window is not closed
	{
		//update Events
		glfwPollEvents();

		//Update logic

		//Clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//clear draw area

		//Draw

		//END
		glfwSwapBuffers(window);//make thinks faster
		glFlush();
	}

	//end
	glfwTerminate();

	return 0;
}