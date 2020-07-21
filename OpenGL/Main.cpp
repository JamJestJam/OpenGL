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
	inFile.open("Shaders\\vertex_core.glsl");//open file

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
	inFile.open("Shaders\\fragment_core.glsl");//open file

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

GLuint LoadTexture(string ImageName) {
	string src = "./Images/" + ImageName + ".png";
	int imageWidth = 0, imageHeight = 0;
	//load image                           image src    variable width and height  null  rgba-with alfa chanel
	unsigned char* image = SOIL_load_image(src.c_str(), &imageWidth, &imageHeight, NULL, SOIL_LOAD_RGBA);

	GLuint texture;
	glGenTextures(1, &texture);//create space to texture
	glBindTexture(GL_TEXTURE_2D, texture);//set buffer, type to texture 2D and use it

	//set options to texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//if texture is smaller then object, texture repet on width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//if texture is smaller then object, texture repet on height
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);//antyaliasing to the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//antyaliasing to the texture

	if (!image)//if is not something in image
	{
		cout << "texture load fail" << endl;
	}
	else {
		//generate texture image
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);//generate texture in several difren resolutions
	}

	glActiveTexture(0);//unactivate texture
	glBindTexture(GL_TEXTURE_2D, 0);//unbind texture
	SOIL_free_image_data(image);//remove image data from ram

	return texture;
}

void UpdateInput(GLFWwindow *window, vec3& position, vec3& rotation, vec3& scale) {
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
	GLuint coreProgram;//create new shader programs
	if (!LoadShaders(coreProgram)) {//load shaders & check if is success
		glfwTerminate();
	}

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
	GLuint texture0 = LoadTexture("Light");
	GLuint texture1 = LoadTexture("Box");

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
	vec3 lightPos0(0.f,0.f,2.f);//light position

	//use transofrmation
	glUseProgram(coreProgram);//use vertex shader
	glUniformMatrix4fv(glGetUniformLocation(coreProgram, "ModelMatrix"), 1, GL_FALSE, value_ptr(ModelMatrix));//send matrix 4v4 
	//use perspective
	glUniformMatrix4fv(glGetUniformLocation(coreProgram, "ViewMatrix"), 1, GL_FALSE, value_ptr(ViewMatrix));//send matrix 4v4
	glUniformMatrix4fv(glGetUniformLocation(coreProgram, "ProjectionMatrix"), 1, GL_FALSE, value_ptr(ProjectionMatrix));//send matrix 4v4
	//use light
	glUniform3fv(glGetUniformLocation(coreProgram, "LightPos0"), 1, value_ptr(lightPos0));

	glUseProgram(0);//stop using vertex shader

	glClearColor(0, 0, 0, 1);//set clear color to RGBA
	//main loop
	while (!glfwWindowShouldClose(window))//while window is not closed
	{
		//update Events
		glfwPollEvents();

		//Update logic
		UpdateInput(window);
		UpdateInput(window, position, rotation, scale);

		//Clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);//clear draw area

		//use a shader/program
		glUseProgram(coreProgram);

		//update uniforms
		glUniform1i(glGetUniformLocation(coreProgram, "texture0"), 0);
		glUniform1i(glGetUniformLocation(coreProgram, "texture1"), 1);

		//move rotate and scale every loop
		ModelMatrix = mat4(1.f);
		ModelMatrix = translate(ModelMatrix, position);//move
		ModelMatrix = rotate(ModelMatrix, radians(rotation.x), vec3(1.f, 0.f, 0.f));//rotation x
		ModelMatrix = rotate(ModelMatrix, radians(rotation.y), vec3(0.f, 1.f, 0.f));//rotation y 
		ModelMatrix = rotate(ModelMatrix, radians(rotation.z), vec3(0.f, 0.f, 1.f));//rotation z
		ModelMatrix = glm::scale(ModelMatrix, scale);//scale
		//use new tranformations
		glUniformMatrix4fv(glGetUniformLocation(coreProgram, "ModelMatrix"), 1, GL_FALSE, value_ptr(ModelMatrix));//send matrix 4v4

		//use perspective
		glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);//get size of drawarea //it must be change its only for test
		ProjectionMatrix = mat4(1.f);
		ProjectionMatrix = perspective(
			radians(fov),
			static_cast<float>(framebufferWidth) / framebufferHeight,
			nearPlane,
			farPlane
		);
		glUniformMatrix4fv(glGetUniformLocation(coreProgram, "ProjectionMatrix"), 1, GL_FALSE, value_ptr(ProjectionMatrix));//send matrix 4v4

		//activate texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

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
	}

	//end
	glfwDestroyWindow(window);//close window
	glfwTerminate();//close draw area

	//delete program
	glDeleteProgram(coreProgram);

	return 0;
}