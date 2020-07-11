#version 440

//inform graphic card about data in pipeline
in vec3 vs_position;
in vec3 vs_color;
in vec3 vs_texcoords;

//inform graphic card about data out from pipeline
out vec4 fs_color;

void main()
{
	fs_color = vec4(vs_color, 1.f);//set color with no thransparency
} 