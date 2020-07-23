#pragma once

#include <glm.hpp>
#include <vec3.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
	glm::vec3 normal;
};
