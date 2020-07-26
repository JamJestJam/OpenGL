#include "Game.h"

Game::Game(const char* windowName, const int width, const int height, const int GLversion, const int GLsubVersion, bool resizable) :
	windowWidth(width), windowheight(height), GLmajorVer(GLversion), GLminorVer(GLsubVersion)
{
	this->InitGLFW();
	this->InitWindow(windowName, resizable);
	this->InitGLEW();
	this->initOpenGL();
}

Game::~Game() {
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

bool Game::GetWindowShouldClose()
{
	return !(glfwWindowShouldClose(this->window));
}

void Game::MakeWindowsShouldClose(){
	glfwSetWindowShouldClose(window, GLFW_TRUE);//close window
}

void Game::InitWindow(const char* windowName, bool resizable) {
	//glfw setings
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//core version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GLmajorVer);//set version 4.4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GLminorVer);
	glfwWindowHint(GLFW_RESIZABLE, resizable);//don't allow windows resible

	this->window = glfwCreateWindow(this->windowWidth, this->windowheight, windowName, NULL, NULL);//create new window

	if (this->window == nullptr)
	{
		std::cout << "ERROR::GLFW_WINDOWS_INIT_FAIL" << std::endl;
	}

	//callback of change window size
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);//get size of drawarea
	glfwSetFramebufferSizeCallback(this->window, this->Framebuffer_resize_callback);//on window event "resize" callback function

	glfwMakeContextCurrent(this->window);//show window
}

void Game::InitGLFW() {
	//init glfw
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "ERROR::GLFW_INIT_FAIL" << std::endl;
		glfwTerminate();
	}
}

void Game::InitGLEW(){
	glewExperimental = GL_TRUE;//init glew

	if (glewInit() != GLEW_OK)//check if its okey
	{
		std::cout << "ERROR::GLEW_INIT_FAIL" << std::endl;//show error in console
		glfwTerminate();//terminate glfw
	}
}

void Game::initOpenGL(){
	glEnable(GL_DEPTH_TEST);//enable using Z coords on the screen

	glEnable(GL_CULL_FACE);//don't draw faces
	glCullFace(GL_BACK);//don't draw back face
	glFrontFace(GL_CCW);//set fron face to face that the vector edges is counterclockwise

	glEnable(GL_BLEND);//enable blending colors
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//set color thransparent

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//fill the shape with a color
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//draw only edges
}

void Game::Update() {

}

void Game::Render() {

}

void Game::Framebuffer_resize_callback(GLFWwindow* win, int frameBufferWidth, int frameBufferHeight) {
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);//set new draw area size
}