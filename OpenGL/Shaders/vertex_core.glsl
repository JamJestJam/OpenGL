#version 440

//inform graphic card about data in pipeline
layout (location = 0) in vec3 vertex_position;//first three floats are about position
layout (location = 1) in vec3 vertex_color;//next three floats are about color
layout (location = 2) in vec2 vertex_texcoord;//next two are about texture coords
layout (location = 3) in vec3 vertex_normal;//and last tree are about normal

//inform graphic card about data out from pipeline
out vec3 vs_position;//first three floats are about position
out vec3 vs_color;//next three floats are about color
out vec2 vs_texcoord;//next two are about texture coords
out vec3 vs_normal;//and last tree are about normal

uniform mat4 ModelMatrix;//object transformation
//camera perspective options
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
	//vs_position = vertex_position;//set position
	vs_position = vec4(ModelMatrix * vec4(vertex_position, 1.f)).xyz;
	vs_color = vertex_color;//set color
	vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y * (-1.f));//set texture, inverted along the Y axis
	vs_normal = mat3(ModelMatrix) * vertex_normal;
	
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vertex_position, 1.f);//set vertex position in world
}