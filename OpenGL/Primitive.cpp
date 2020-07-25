#include "Primitive.h"


Primitive::Primitive() {

}

Primitive::~Primitive() {

}

void Primitive::Set(const Vertex* vertices, const unsigned nrOfvertices, const GLuint* indices, const unsigned nrOfindices) {
	//save vetices
	for (size_t i = 0; i < nrOfvertices; i++)
		this->vertices.push_back(vertices[i]);
	//save indices
	for (size_t i = 0; i < nrOfindices; i++)
		this->indices.push_back(indices[i]);
}

Vertex* Primitive::GetVertices() {
	return this->vertices.data();
}

GLuint* Primitive::GetIndices() {
	return this->indices.data();
}

const unsigned Primitive::GetNrOfVertices() {
	return this->vertices.size();
}

const unsigned Primitive::GetNrOfIndices() {
	return this->indices.size();
}

Quad::Quad() : Primitive() {
	Vertex vertices[] = {
		//position						//color							//texcoords				//normal
		glm::vec3(-0.5f,  0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 1.0f),	glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 0.0f),	glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f),	glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.5f,  0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 1.0f),	glm::vec3(0.0f, 0.0f, 1.0f)
	};
	//number of vertices
	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	//use verticles ID
	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3
	};
	//number of vertices in use
	unsigned nrOfindices = sizeof(indices) / sizeof(GLuint);

	//set data
	this->Set(vertices, nrOfVertices, indices, nrOfindices);
}

Triangle::Triangle() {
	Vertex vertices[] = {
		//position						//color							//texcoords				//normal
		glm::vec3(-0.5f,  0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 1.0f),	glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(0.0f, 0.0f),	glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),	glm::vec3(1.0f, 1.0f, 1.0f),	glm::vec2(1.0f, 0.0f),	glm::vec3(0.0f, 0.0f, 1.0f),
	};
	//number of vertices
	unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

	//use verticles ID
	GLuint indices[] = {
		0, 1, 2
	};
	//number of vertices in use
	unsigned nrOfindices = sizeof(indices) / sizeof(GLuint);

	//set data
	this->Set(vertices, nrOfVertices, indices, nrOfindices);
}