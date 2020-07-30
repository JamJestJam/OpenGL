#include "Mesh.h"

Mesh::Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indicesArray, const unsigned& nrOfIndices, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
	this->Init(vertexArray, nrOfVertices, indicesArray, nrOfIndices, position, rotation, scale);
}

Mesh::Mesh(Primitive* primitive, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
	this->Init(primitive->GetVertices(), primitive->GetNrOfVertices(), primitive->GetIndices(), primitive->GetNrOfIndices(), position, rotation, scale);
}

Mesh::~Mesh() {
	///delete data
	glDeleteVertexArrays(1, &this->vao);
	glDeleteBuffers(1, &this->vbo);
	glDeleteBuffers(1, &this->ebo);
}

void Mesh::Init(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indicesArray, const unsigned& nrOfIndices, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
	//set variables
	this->nrOfIndices = nrOfIndices;
	this->nrOfVertices = nrOfVertices;

	this->position = position;
	this->rotation = rotation;
	this->scale = scale;

	//init VAO
	//VAO - buffer for 3D objects
	glCreateVertexArrays(1, &this->vao);//create space to storage 3D object
	glBindVertexArray(this->vao);//set our VAO to activ, all changes will be made at VAO

	//VBO - buffer for verticles
	glGenBuffers(1, &this->vbo);//create space to storage vertex
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);//set buffer type to array and use it
	glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), vertexArray, GL_DYNAMIC_DRAW);//send data to VBO, graphic card memory

	//EBO - buffer for indices
	glGenBuffers(1, &this->ebo);//create space to storage indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);//set buffer type to element array and use it
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), indicesArray, GL_DYNAMIC_DRAW);//send data to EBO, graphic card memory

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

	this->UpdateMatrix();
}

void Mesh::Update() {

}

void Mesh::Render(Shader* shader) {
	//update matrix
	this->UpdateMatrix();
	//update uniforms
	this->UpdateUnifroms(shader);

	shader->Use();

	//bind vertex array object
	glBindVertexArray(this->vao);

	//Draw
	glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);
}

void Mesh::UpdateMatrix() {
	this->modelMatrix = glm::mat4(1.f);

	this->modelMatrix = glm::translate(this->modelMatrix, this->position);//move
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));//rotation x
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));//rotation y 
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));//rotation z
	this->modelMatrix = glm::scale(this->modelMatrix, this->scale);//scale
}

void Mesh::UpdateUnifroms(Shader* shader) {
	shader->SetValueMat4(this->modelMatrix, "ModelMatrix");
}

void Mesh::SetPosition(const glm::vec3 position) {
	this->position = position;
}

void Mesh::SetRotation(const glm::vec3 rotation) {
	this->rotation = rotation;
}

void Mesh::SetScale(const glm::vec3 scale) {
	this->scale = scale;
}

void Mesh::Move(const glm::vec3 move) {
	this->position += move;
}

void Mesh::Rotate(const glm::vec3 rotation) {
	this->rotation += rotation;
}

void Mesh::Scale(const glm::vec3 scale) {
	this->scale += scale;
}
