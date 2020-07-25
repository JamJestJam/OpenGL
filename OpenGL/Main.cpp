#include "Libs.h"

//function load on resize window
void Framebuffer_resize_callback(GLFWwindow* win, int frameBufferWidth, int frameBufferHeight) {
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);//set new draw area size
}

void UpdateInput(GLFWwindow* window, Mesh* mesh) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {//check if esc key is press
		glfwSetWindowShouldClose(window, GLFW_TRUE);//close window
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {//check if esc key is press
		mesh->Move(glm::vec3(0.f, 0.f, -0.01f));
		//position.z -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {//check if esc key is press
		mesh->Move(glm::vec3(-0.01f, 0.f, 0.f));
		//position.x -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {//check if esc key is press
		mesh->Move(glm::vec3(0.f, 0.f, 0.01f));
		//position.z += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {//check if esc key is press
		mesh->Move(glm::vec3(0.01f, 0.f, 0.f));
		//position.x += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {//check if esc key is press
		mesh->Rotate(glm::vec3(0.f, -1.f, 0.f));
		//rotation.y -= 1.f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {//check if esc key is press
		mesh->Rotate(glm::vec3(0.f, 1.f, 0.f));
		//rotation.y += 1.f;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {//check if esc key is press
		mesh->Scale(glm::vec3(0.1f));
		//scale += 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {//check if esc key is press
		mesh->Scale(glm::vec3(-0.1f));
		//scale -= 0.1f;
	}
}

int main() {
	//init glfw
	glfwInit();//init glfw

	//create windows
	const int windowWidth = 640;//window width in px
	const int windowheight = 480;//window height in px
	int framebufferWidth = 0;//drawarea width
	int framebufferHeight = 0;//drawarea height
	const char* title = "Ucze sie";//window title

	//glfw setings
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//core version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//set version 4.4
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);//don't allow windows resible

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowheight, title, NULL, NULL);//create new window

	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);//get size of drawarea
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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//draw only edges

	//shader load
	Shader coreProgram("vertex_core.glsl", "fragment_core.glsl");

	Mesh mesh(&Triangle(), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f));

	//textures
	Texture texture0("Light", 100);
	Texture texture1("Box", 23);

	//material 0
	Material material(glm::vec3(0.008f), glm::vec3(1.f), glm::vec3(1.f), texture0.GetTextureUnit(), texture1.GetTextureUnit());

	//camera init
	glm::vec3 camPosition(0.f, 0.f, 1.f);//camera position
	glm::vec3 wordUP(0.f, 1.f, 0.f);//coordinate to word up
	glm::vec3 camFront(0.f, 0.f, -1.f);//coordinate to camera front

	//perpective init
	glm::mat4 ViewMatrix(1.f);
	ViewMatrix = lookAt(camPosition, camPosition + camFront, wordUP);//camera look at

	float fov = 90.f;//angle beetwen draw area and line draw
	float nearPlane = 0.1f;//lenght from camera to draw area
	float farPlane = 1000.f;//lenght how far can you see
	glm::mat4 ProjectionMatrix(1.f);
	ProjectionMatrix = glm::perspective(
		glm::radians(fov),
		static_cast<float>(framebufferWidth) / framebufferHeight,
		nearPlane,
		farPlane
	);

	//Light
	glm::vec3 lightPos0(0.f, 0.f, 0.f);//light position

	//use perspective
	coreProgram.SetValueMat4(ViewMatrix, "ViewMatrix");
	coreProgram.SetValueMat4(ProjectionMatrix, "ProjectionMatrix");
	//use light
	coreProgram.SetValueVec3(lightPos0, "LightPos0");
	coreProgram.SetValueVec3(camPosition, "CameraPos");

	glUseProgram(0);//stop using vertex shader

	glClearColor(0, 0, 0, 1);//set clear color to RGBA
	//main loop
	while (!glfwWindowShouldClose(window))//while window is not closed
	{
		//update Events
		glfwPollEvents();

		//Update logic
		UpdateInput(window, &mesh);

		//Clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//clear draw area

		//use perspective
		glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);//get size of drawarea //it must be change its only for test
		ProjectionMatrix = glm::mat4(1.f);
		ProjectionMatrix = glm::perspective(
			glm::radians(fov),
			static_cast<float>(framebufferWidth) / framebufferHeight,
			nearPlane,
			farPlane
		);

		coreProgram.SetValueMat4(ProjectionMatrix, "ProjectionMatrix");

		//update uniforms
		material.sendToShader(coreProgram);

		//use a shader/program
		coreProgram.Use();

		//activate texture
		texture0.Bind();
		texture1.Bind();

		//draw
		mesh.Rednder(&coreProgram);

		//END
		glfwSwapBuffers(window);//make thinks faster
		glFlush();

		//unbind texture
		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		coreProgram.UnUse();
	}

	//end
	glfwDestroyWindow(window);//close window
	glfwTerminate();//close draw area

	return 0;
}