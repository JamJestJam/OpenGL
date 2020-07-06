#pragma once

#define DllImport   __declspec("dll/glew32.dll")

//console
#include <iostream>
//add functions to draw
#include <glew.h>
//create window and draw area
#include <glfw3.h>

//funny mathematics
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//load imagest etc
#include <SOIL2.h>

using namespace std;
using namespace glm;