#include "Libs.h"

//triangle 
Vertex vertices[] = {
	//triangle
	//position					//color					//texcoords			//normal
	vec3(-0.5f,  0.5f, 0.0f),	vec3(1.0f, 1.0f, 1.0f),	vec2(0.0f, 1.0f),	vec3(0.0f, 0.0f, -1.0f),
	vec3(-0.5f, -0.5f, 0.0f),	vec3(1.0f, 1.0f, 1.0f),	vec2(0.0f, 0.0f),	vec3(0.0f, 0.0f, -1.0f),
	vec3(0.5f, -0.5f, 0.0f),	vec3(1.0f, 1.0f, 1.0f),	vec2(1.0f, 0.0f),	vec3(0.0f, 0.0f, -1.0f),
	vec3(0.5f,  0.5f, 0.0f),	vec3(1.0f, 1.0f, 1.0f),	vec2(1.0f, 1.0f),	vec3(0.0f, 0.0f, -1.0f)
};
//number of vertices in triangle
unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

//use verticles ID
GLuint indices[] = {
	0, 1, 2,		//triangle 1
	0, 2, 3			//triangle 2
};
//number of vertices in use
unsigned nrOfindices = sizeof(indices) / sizeof(GLuint);

//function load on resize window
void Framebuffer_resize_callback(GLFWwindow* win, int frameBufferWidth, int frameBufferHeight) {
	glViewport(0, 0, frameBufferWidth, frameBufferHeight);//set new draw area size
}

void UpdateInput(GLFWwindow *window, vec3& position, vec3& rotation, vec3& scale) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {//check if esc key is press
		glfwSetWindowShouldClose(window, GLFW_TRUE);//close window
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {//check if esc key is press
		position.z -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {//check if esc key is press
		position.x -= 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {//check if esc key is press
		position.z += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {//check if esc key is press
		position.x += 0.01f;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {//check if esc key is press
		rotation.y -= 1.f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {//check if esc key is press
		rotation.y += 1.f;
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {//check if esc key is press
		scale += 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {//check if esc key is press
		scale -= 0.1f;
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

	//VAO - buffer for 3D objects
	GLuint VAO;
	glCreateVertexArrays(1, &VAO);//create space to storage 3D object
	glBindVertexArray(VAO);//set our VAO to activ, all changes will be made at VAO

	//VBO - buffer for verticles
	GLuint VBO;
	glGenBuffers(1, &VBO);//create space to storage vertex
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//set buffer type to array and use it
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);//send data to VBO, graphic card memory

	//EBO - buffer for indices
	GLuint EBO;
	glGenBuffers(1, &EBO);//create space to storage indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//set buffer type to element array and use it
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);//send data to EBO, graphic card memory

	//let the graphics cards know what the float array, we send represents.
	//first element, element lengh, data type, normalize, size to next vertex position, pointer to next atribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));//position
	glEnableVertexAttribArray(0);//enable position
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));//color
	glEnableVertexAttribArray(1);//enable color
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));//texture
	glEnableVertexAttribArray(2);//enable texture
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));//texture
	glEnableVertexAttribArray(3);//enable normal

	glBindVertexArray(0);//Exit editing VAO

	vec4 tmp = vec4(1, 2, 3, 4);

	//textures
	Texture texture0("Light", 100);
	Texture texture1("Box", 23);

	//transform 
	mat4 ModelMatrix(1.f);

	vec3 position(0.f);
	vec3 rotation(0.f);
	vec3 scale(1.f);

	//transofrm once
	ModelMatrix = translate(ModelMatrix, position);//move
	ModelMatrix = rotate(ModelMatrix, radians(rotation.x), vec3(1.f, 0.f, 0.f));//rotation x
	ModelMatrix = rotate(ModelMatrix, radians(rotation.y), vec3(0.f, 1.f, 0.f));//rotation y 
	ModelMatrix = rotate(ModelMatrix, radians(rotation.z), vec3(0.f, 0.f, 1.f));//rotation z
	ModelMatrix = glm::scale(ModelMatrix, scale);//scale

	//camera init
	vec3 camPosition(0.f, 0.f, 1.f);//camera position
	vec3 wordUP(0.f, 1.f, 0.f);//coordinate to word up
	vec3 camFront(0.f, 0.f, -1.f);//coordinate to camera front

	//perpective init
	mat4 ViewMatrix(1.f);
	ViewMatrix = lookAt(camPosition, camPosition + camFront, wordUP);//camera look at

	float fov = 90.f;//angle beetwen draw area and line draw
	float nearPlane = 0.1f;//lenght from camera to draw area
	float farPlane = 1000.f;//lenght how far can you see
	mat4 ProjectionMatrix(1.f);
	ProjectionMatrix = perspective(
		radians(fov),
		static_cast<float>(framebufferWidth) / framebufferHeight,
		nearPlane,
		farPlane
	);

	//Light
	vec3 lightPos0(0.f,0.f,0.f);//light position

	//use transofrmation
	coreProgram.SetValueMat4(ModelMatrix, "ModelMatrix");//use transformations
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
		UpdateInput(window, position, rotation, scale);

		//Clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//clear draw area

		//update uniforms
		coreProgram.SetValue1i(texture0.GetTextureUnit(), "texture0");
		coreProgram.SetValue1i(texture1.GetTextureUnit(), "texture1");

		//move rotate and scale every loop
		ModelMatrix = mat4(1.f);
		ModelMatrix = translate(ModelMatrix, position);//move
		ModelMatrix = rotate(ModelMatrix, radians(rotation.x), vec3(1.f, 0.f, 0.f));//rotation x
		ModelMatrix = rotate(ModelMatrix, radians(rotation.y), vec3(0.f, 1.f, 0.f));//rotation y 
		ModelMatrix = rotate(ModelMatrix, radians(rotation.z), vec3(0.f, 0.f, 1.f));//rotation z
		ModelMatrix = glm::scale(ModelMatrix, scale);//scale
		//use new tranformations
		coreProgram.SetValueMat4(ModelMatrix, "ModelMatrix");

		//use perspective
		glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);//get size of drawarea //it must be change its only for test
		ProjectionMatrix = mat4(1.f);
		ProjectionMatrix = perspective(
			radians(fov),
			static_cast<float>(framebufferWidth) / framebufferHeight,
			nearPlane,
			farPlane
		);
		coreProgram.SetValueMat4(ProjectionMatrix, "ProjectionMatrix");

		//use a shader/program
		coreProgram.Use();

		//activate texture
		texture0.Bind();
		texture1.Bind();

		//bind vertex array object
		glBindVertexArray(VAO);

		//Draw
		//glDrawArrays(GL_TRIANGLES, 0, nrOfVertices);
		glDrawElements(GL_TRIANGLES, nrOfindices, GL_UNSIGNED_INT, 0);

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