#include "Libs.h"

//function to update input state
void UpdateInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {//check if esc key is press
		glfwSetWindowShouldClose(window, GLFW_TRUE);//close window
	}
}

//function load on resize window
void Framebuffer_resize_callback(GLFWwindow* win, int frameBufferWidth, int frameBufferHeight) {
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);//set new draw area size
}

//function to load shader
bool LoadShaders(GLuint& program)
{
	bool loadSuccess = true;
	char infoLog[512];//info about errors for example. program isn't able to link or a shader isn't able to compile etc.
	GLint success;//this will be used to determine if the shader has loaded correctly

	string temp = "";//used to get line
	string src = "";//save data

	ifstream inFile;//fsteream file

	//vertex shader
	inFile.open("vertex_core.glsl");//open file

	if (inFile.is_open()) {//check if file is open
		while (getline(inFile, temp)) {//read all lines
			src += temp + "\n";//add line to src
		}
	}
	else {//if is not open
		cout << "Shader init failed, vertex read file\n";//show error
		loadSuccess = false;
	}
	inFile.close();//close file

	//create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);//create shader id
	const GLchar* vertSrc = src.c_str();//create shader source
	glShaderSource(vertexShader, 1, &vertSrc, NULL);//set shader source
	glCompileShader(vertexShader);//compile vertex shader

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//get compile status
	if (!success) {//error check
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "Shader init failed, vertex compile error\n";//show error
		cout << infoLog << endl;//show shader log 
		loadSuccess = false;
	}

	temp = "";//clear temp
	src = "";//clear src

	//fragment shader
	inFile.open("fragment_core.glsl");//open file

	if (inFile.is_open()) {//check if file is open
		while (getline(inFile, temp)) {//read all lines
			src += temp + "\n";//add line to src
		}
	}
	else {//if is not open
		cout << "Shader init failed, fragment read file\n";//show error
		loadSuccess = false;
	}
	inFile.close();//close file

	//create fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//create shader id
	const GLchar* fragtSrc = src.c_str();//create shader source
	glShaderSource(fragmentShader, 1, &fragtSrc, NULL);//set shader source
	glCompileShader(fragmentShader);//compile vertex shader

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);//get compile status
	if (!success) {//error check
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "Shader init failed, fragment compile error\n";//show error
		cout << infoLog << endl;//show shader log 
		loadSuccess = false;
	}

	//program
	program = glCreateProgram();//create program

	glAttachShader(program, vertexShader);//attach shader
	glAttachShader(program, fragmentShader);//attach shader
	glLinkProgram(program);//connect everything together

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "Program linking error\n";//show error
		cout << infoLog << endl;//show program log 
		loadSuccess = false;
	}

	//end of program
	glUseProgram(0);//reset program which is currently using
	glDeleteShader(vertexShader);//delete shader !important
	glDeleteShader(fragmentShader);//delete shader !important

	return loadSuccess;
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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//set version 4.4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
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

	//opengl options
	glEnable(GL_DEPTH_TEST);//enable using Z coords on the screen

	glEnable(GL_CULL_FACE);//don't draw faces
	glCullFace(GL_BACK);//don't draw back face
	glFrontFace(GL_CCW);//set fron face to face that the vector edges is counterclockwise

	glEnable(GL_BLEND);//enable blending colors
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//set color thransparent

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//fill the shape with a color

	//shader load
	GLuint coreProgram;//create new shader programs
	if (!LoadShaders(coreProgram)) {//load shaders & check if is success
		glfwTerminate();
	}
	glClearColor(1, 1, 1, 1);//set clear color to RGBA
	//main loop
	while (!glfwWindowShouldClose(window))//while window is not closed
	{
		//update Events
		glfwPollEvents();

		//Update logic
		UpdateInput(window);

		//Clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//clear draw area

		//Draw

		//END
		glfwSwapBuffers(window);//make thinks faster
		glFlush();
	}

	//end
	glfwDestroyWindow(window);//close window
	glfwTerminate();//close draw area

	//delete program
	glDeleteProgram(coreProgram);

	return 0;
}