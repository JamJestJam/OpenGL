#pragma once
#include "Libs.h";

class Game
{
public:
	/// <summary>
	/// Create new game class
	/// </summary>
	/// <returns></returns>
	Game(const char* windowName, const int width = 480, const int height = 320, const int GLversion = 3, const int GLsubVersion = 3, bool resizable = true);
	/// <summary>
	/// Delete game class
	/// </summary>
	virtual ~Game();
	/// <summary>
	/// check if windows should close
	/// </summary>
	bool GetWindowShouldClose();
	void MakeWindowsShouldClose();

private:
	//windows params
	/// <summary>
	/// Window
	/// </summary>
	GLFWwindow* window;
	/// <summary>
	/// window width
	/// </summary>
	const int windowWidth;
	/// <summary>
	/// window height
	/// </summary>
	const int windowheight;
	/// <summary>
	/// drawarea width
	/// </summary>
	int framebufferWidth;
	/// <summary>
	/// drawarea height
	/// </summary>
	int framebufferHeight;

	//openGL version
	const int GLmajorVer;
	const int GLminorVer;

	//Matrices camera
	glm::mat4 viewMatrix;
	glm::vec3 camPosition;
	glm::vec3 worldUp;
	glm::vec3 camFront;
	glm::mat4 projectionMatrix;
	float fov;
	float nearPlane;
	float farPlane;

	//Shaders
	std::vector<Shader*> shaders;
	//Textures
	std::vector<Texture*> textures;
	//Materials
	std::vector<Material*> materials;
	//Meshes
	std::vector<Mesh*> meshes;
	//Lights
	std::vector<glm::vec3*> lights;

	/// <summary>
	/// Initialize window
	/// </summary>
	void InitWindow(const char* windowName, bool resizable);
	/// <summary>
	/// Initialize GLFW
	/// </summary>
	void InitGLFW();
	/// <summary>
	/// Initialize FLEW
	/// </summary>
	void InitGLEW();
	/// <summary>
	/// Initialize OpenGL options
	/// </summary>
	void InitOpenGL();
	/// <summary>
	/// Init perspective
	/// </summary>
	void InitMatrices();

	//init
	void InitShaders();
	void InitTextures();
	void InitMaterials();
	void InitMeshes();
	void InitLights();
	void InitUniforms();

	/// <summary>
	/// Update uniform for perspective
	/// </summary>
	void UpdateUniforms();

	//static functions
	/// <summary>
	/// Callback on change window size
	/// </summary>
	static void Framebuffer_resize_callback(GLFWwindow* win, int frameBufferWidth, int frameBufferHeight);
	static void UpdateInput(GLFWwindow* win, Mesh* mesh);//tmp
public:
	/// <summary>
	/// Update logic
	/// </summary>
	void Update();
	/// <summary>
	/// Render stuf
	/// </summary>
	void Render();
};

