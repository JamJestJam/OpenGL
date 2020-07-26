#pragma once
#include "Libs.h";

class Game
{
public:
	/// <summary>
	/// Create new game class
	/// </summary>
	/// <returns></returns>
	Game(const char* windowName, const int width = 480, const int height = 320, const int GLversion = 4, const int GLsubVersion = 4, bool resizable = false);
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
	void initOpenGL();
	/// <summary>
	/// Update logic
	/// </summary>
	void Update();
	/// <summary>
	/// Render stuf
	/// </summary>
	void Render();
	/// <summary>
	/// Callback on change window size
	/// </summary>
	static void Framebuffer_resize_callback(GLFWwindow* win, int frameBufferWidth, int frameBufferHeight);
};

