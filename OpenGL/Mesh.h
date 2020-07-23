#pragma once

#include <iostream>
#include <vector>

#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"


class Mesh
{
public:
	/// <summary>
	/// Create new Mesh
	/// </summary>
	/// <param name="vertexArray">array of vertexs</param>
	/// <param name="nrOfVertices">vertex array lenght</param>
	/// <param name="indexArray">array of indexs</param>
	/// <param name="nrOfIndices">index array lenght</param>
	Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices);
	/// <summary>
	/// Delete mesh
	/// </summary>
	~Mesh();
	/// <summary>
	/// Update Mesh data
	/// </summary>
	void Update();
	/// <summary>
	/// Render mesh
	/// </summary>
	/// <param name="shader">shader</param>
	void Rednder(Shader* shader);
private:
	/// <summary>
	/// Update shader uniforms
	/// </summary>
	/// <param name="shader">shader</param>
	void UpdateUnifroms(Shader* shader);
	/// <summary>
	/// vertices list
	/// </summary>
	std::vector<Vertex> vertices;
	/// <summary>
	/// List of verticels to use
	/// </summary>
	std::vector<GLuint> indices;
	/// <summary>
	/// buffer in graphics card for mesh
	/// </summary>
	GLuint vao;
	/// <summary>
	/// buffer in graphics card for verticles
	/// </summary>
	GLuint vbo;
	/// <summary>
	/// buffer in graphics card for indices
	/// </summary>
	GLuint ebo;
	/// <summary>
	/// Mesh position
	/// </summary>
	glm::vec3 position;
	/// <summary>
	/// Mesh rotation
	/// </summary>
	glm::vec3 rotation;
	/// <summary>
	/// Mesh scale
	/// </summary>
	glm::vec3 scale;
	/// <summary>
	/// Mesh transformation
	/// </summary>
	glm::mat4 modelMatrix;
};

