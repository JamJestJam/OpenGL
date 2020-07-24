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
	/// <param name="indicesArray">indices array lenght</param>
	Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indicesArray, const unsigned& nrOfIndices,
		glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
	/// <summary>
	/// Delete mesh
	/// </summary>
	~Mesh();
	/// <summary>
	/// set new mesh positon
	/// </summary>
	/// <param name="position">new position</param>
	void SetPosition(const glm::vec3 position);
	/// <summary>
	/// set new mesh rotation
	/// </summary>
	/// <param name="rotation">new rotation</param>
	void SetRotation(const glm::vec3 rotation);
	/// <summary>
	/// set new mesh scale
	/// </summary>
	/// <param name="scale">new scale</param>
	void SetScale(const glm::vec3 scale);
	/// <summary>
	/// move the mesh by the indicated vector
	/// </summary>
	/// <param name="move">displacement vector</param>
	void Move(const glm::vec3 move);
	/// <summary>
	/// rotate the mesh by the indicated vector
	/// </summary>
	/// <param name="rotation">displacement vector</param>
	void Rotate(const glm::vec3 rotation);
	/// <summary>
	/// scale the mesh by the indicated vector
	/// </summary>
	/// <param name="scale">displacement vector</param>
	void Scale(const glm::vec3 scale);
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
	/// update matrix data
	/// </summary>
	void UpdateMatrix();
	/// <summary>
	/// number of vertices
	/// </summary>
	unsigned nrOfVertices;
	/// <summary>
	/// number of indices
	/// </summary>
	unsigned nrOfIndices;
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

