#include "Game.h"

Game::Game(const char* windowName, const int width, const int height, const int GLversion, const int GLsubVersion, bool resizable) :
	windowWidth(width), windowheight(height), GLmajorVer(GLversion), GLminorVer(GLsubVersion) {
	//init var
	this->window = nullptr;
	this->framebufferWidth = this->windowWidth;
	this->framebufferHeight = this->windowheight;

	this->camPosition = glm::vec3(0.f, 0.f, 1.f);
	this->worldUp = glm::vec3(0.f, 1.f, 0.f);
	this->camFront = glm::vec3(0.f, 0.f, -1.f);

	this->fov = 90.f;
	this->nearPlane = 0.1f;
	this->farPlane = 1000.f;

	//init fun
	this->InitGLFW();
	this->InitWindow(windowName, resizable);
	this->InitGLEW();
	this->InitOpenGL();
	this->InitMatrices();

	this->InitShaders();
	this->InitTextures();
	this->InitMaterials();
	this->InitMeshes();
	this->InitLights();
	this->InitUniforms();
}

Game::~Game() {
	glfwDestroyWindow(this->window);
	glfwTerminate();

	for (size_t i = 0; i < this->shaders.size(); i++)
		delete this->shaders[i];
	for (size_t i = 0; i < this->textures.size(); i++)
		delete this->textures[i];
	for (size_t i = 0; i < this->materials.size(); i++)
		delete this->materials[i];
	for (size_t i = 0; i < this->meshes.size(); i++)
		delete this->meshes[i];
	for (size_t i = 0; i < this->lights.size(); i++)
		delete this->lights[i];
}

bool Game::GetWindowShouldClose()
{
	return !(glfwWindowShouldClose(this->window));
}

void Game::MakeWindowsShouldClose() {
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

void Game::InitGLEW() {
	glewExperimental = GL_TRUE;//init glew

	if (glewInit() != GLEW_OK)//check if its okey
	{
		std::cout << "ERROR::GLEW_INIT_FAIL" << std::endl;//show error in console
		glfwTerminate();//terminate glfw
	}
}

void Game::InitOpenGL() {
	glEnable(GL_DEPTH_TEST);//enable using Z coords on the screen

	glEnable(GL_CULL_FACE);//don't draw faces
	glCullFace(GL_BACK);//don't draw back face
	glFrontFace(GL_CCW);//set fron face to face that the vector edges is counterclockwise

	glEnable(GL_BLEND);//enable blending colors
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//set color thransparent

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//fill the shape with a color
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//draw only edges

	glClearColor(0, 0, 0, 1);//set clear color to RGBA
}

void Game::InitMatrices() {
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	this->viewMatrix = glm::mat4(1.f);
	this->viewMatrix = glm::lookAt(this->camPosition, this->camPosition + this->camFront, this->worldUp);

	this->projectionMatrix = glm::mat4(1.f);
	this->projectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane
	);
}

void Game::InitShaders() {
	shaders.push_back(new Shader(
		this->GLmajorVer, this->GLminorVer,
		"vertex_core.glsl", "fragment_core.glsl")
	);
}

void Game::InitTextures() {
	textures.push_back(new Texture("container"));
	textures.push_back(new Texture("container_specular"));

	textures.push_back(new Texture("pusheen"));
	textures.push_back(new Texture("pusheen_specular"));
}

void Game::InitMaterials() {
	materials.push_back(new Material(
		glm::vec3(0.008f), glm::vec3(1.f), glm::vec3(1.f),
		0, 1)
	);
}

void Game::InitMeshes() {
	meshes.push_back(new Mesh(&Quad(),
		glm::vec3(0.f), 
		glm::vec3(0.f), 
		glm::vec3(1.f)
		));

	meshes.push_back(new Mesh(&Quad(),
		glm::vec3(0.f, 0.75f, 0.f),
		glm::vec3(0.f),
		glm::vec3(0.5f)
	));
}

void Game::InitLights() {
	lights.push_back(new glm::vec3(0.f, 0.f, 1.f));
}

void Game::InitUniforms() {
	//use perspective
	shaders[0]->SetValueMat4(this->viewMatrix, "ViewMatrix");
	shaders[0]->SetValueMat4(this->projectionMatrix, "ProjectionMatrix");
	//use light
	shaders[0]->SetValueVec3(*this->lights[0], "LightPos0");
	shaders[0]->SetValueVec3(this->camPosition, "CameraPos");
}

void Game::UpdateUniforms(){
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	this->projectionMatrix = glm::mat4(1.f);
	this->projectionMatrix = glm::perspective(
		glm::radians(this->fov),
		static_cast<float>(this->framebufferWidth) / this->framebufferHeight,
		this->nearPlane,
		this->farPlane
	);

	this->shaders[0]->SetValueMat4(this->projectionMatrix, "ProjectionMatrix");
}

void Game::Update() {
	//update Events
	glfwPollEvents();

	//Update logic
	UpdateInput(this->window, meshes[0]);
}

void Game::Render() {
	//Clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//clear draw area

	//use perspective
	this->InitMatrices();

	//update uniforms
	this->UpdateUniforms();
	this->materials[0]->sendToShader(*this->shaders[0]);

	//use a shader/program
	this->shaders[0]->Use();

	//activate texture
	this->textures[0]->Bind(0);
	this->textures[1]->Bind(1);
	//draw
	this->meshes[0]->Render(this->shaders[0]);

	//activate texture
	this->textures[2]->Bind(0);
	this->textures[3]->Bind(1);
	//draw
	this->meshes[1]->Render(this->shaders[0]);

	//END
	glfwSwapBuffers(this->window);//make thinks faster
	glFlush();

	//unbind texture
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//stop using shader
	this->shaders[0]->UnUse();
}

void Game::Framebuffer_resize_callback(GLFWwindow* win, int frameBufferWidth, int frameBufferHeight) {
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);//set new draw area size
}

void Game::UpdateInput(GLFWwindow* win, Mesh* mesh){
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS) {//check if esc key is press
		glfwSetWindowShouldClose(win, GLFW_TRUE);//close window
	}
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {//check if esc key is press
		mesh->Move(glm::vec3(0.f, 0.f, -0.01f));
	}
	if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {//check if esc key is press
		mesh->Move(glm::vec3(-0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {//check if esc key is press
		mesh->Move(glm::vec3(0.f, 0.f, 0.01f));
	}
	if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {//check if esc key is press
		mesh->Move(glm::vec3(0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS) {//check if esc key is press
		mesh->Rotate(glm::vec3(0.f, -1.f, 0.f));
	}
	if (glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS) {//check if esc key is press
		mesh->Rotate(glm::vec3(0.f, 1.f, 0.f));
	}
	if (glfwGetKey(win, GLFW_KEY_Z) == GLFW_PRESS) {//check if esc key is press
		mesh->Scale(glm::vec3(0.1f));
	}
	if (glfwGetKey(win, GLFW_KEY_X) == GLFW_PRESS) {//check if esc key is press
		mesh->Scale(glm::vec3(-0.1f));
	}
}
