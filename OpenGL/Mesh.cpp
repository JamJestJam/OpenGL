#include "Mesh.h"

Mesh::Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices) {
	//init vertex data
	for (size_t i = 0; i < nrOfVertices; i++)
		this->vertices.push_back(vertexArray[i]);
	//init indices data
	for (size_t i = 0; i < nrOfIndices; i++)
		this->indices.push_back(indexArray[i]);

	//init VAO
	//VAO - buffer for 3D objects
	glCreateVertexArrays(1, &this->vao);//create space to storage 3D object
	glBindVertexArray(this->vao);//set our VAO to activ, all changes will be made at VAO

	//VBO - buffer for verticles
	glGenBuffers(1, &this->vbo);//create space to storage vertex
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);//set buffer type to array and use it
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_DYNAMIC_DRAW);//send data to VBO, graphic card memory

	//EBO - buffer for indices
	glGenBuffers(1, &this->ebo);//create space to storage indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);//set buffer type to element array and use it
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), this->indices.data(), GL_DYNAMIC_DRAW);//send data to EBO, graphic card memory

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

	//init model matrix
	this->position = glm::vec3(0.f);
	this->rotation = glm::vec3(0.f);
	this->scale = glm::vec3(1.f);
	this->modelMatrix = glm::mat4(1.f);

	this->modelMatrix = translate(this->modelMatrix, position);//move
	this->modelMatrix = rotate(this->modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));//rotation x
	this->modelMatrix = rotate(this->modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));//rotation y 
	this->modelMatrix = rotate(this->modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));//rotation z
	this->modelMatrix = glm::scale(this->modelMatrix, scale);//scale
}

Mesh::~Mesh() {
	///delete data
	glDeleteVertexArrays(1, &this->vao);
	glDeleteBuffers(1, &this->vbo);
	glDeleteBuffers(1, &this->ebo);
}

void Mesh::Update() {

}

void Mesh::Rednder(Shader* shader) {
	//update uniforms
	this->UpdateUnifroms(shader);

	shader->Use();

	//bind vertex array object
	glBindVertexArray(this->vao);

	//Draw
	if (this->indices.empty())
		glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	else
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::UpdateUnifroms(Shader* shader) {
	shader->SetValueMat4(this->modelMatrix, "ModelMatrix");
}