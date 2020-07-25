#pragma once

#include <vector>
#include <glew.h>
#include <glfw3.h>
#include "Vertex.h"

class Primitive {
public:
	/// <summary>
	/// create new primitive
	/// </summary>
	Primitive();
	/// <summary>
	/// delete primitive
	/// </summary>
	virtual ~Primitive();
	/// <summary>
	/// Set primitiv vertices
	/// </summary>
	/// <param name="vertices">array of vertices</param>
	/// <param name="nrOfvertices">vertices array lenght</param>
	/// <param name="indices">array of indices</param>
	/// <param name="nrOfindices">indices array lenght</param>
	void Set(const Vertex* vertices, const unsigned nrOfvertices, const GLuint* indices, const unsigned nrOfindices);
	/// <summary>
	/// Return vertices array
	/// </summary>
	Vertex* GetVertices();
	/// <summary>
	/// Return indices array
	/// </summary>
	GLuint* GetIndices();
	/// <summary>
	/// Return number of vertices
	/// </summary>
	/// <returns></returns>
	const unsigned GetNrOfVertices();
	/// <summary>
	/// Return number of indices
	/// </summary>
	const unsigned GetNrOfIndices();
private:
	/// <summary>
	/// List of vertices
	/// </summary>
	std::vector<Vertex> vertices;
	/// <summary>
	/// List of vertices ID to draw
	/// </summary>
	std::vector<GLuint> indices;
};

static class Quad : public Primitive {
public:
	Quad();
};

static class Triangle : public Primitive {
public:
	Triangle();
};