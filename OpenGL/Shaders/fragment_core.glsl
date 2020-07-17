#version 440

//inform graphic card about data in pipeline
in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;

//inform graphic card about data out from pipeline
out vec4 fs_color;

uniform sampler2D texture0;//take pixel color from the image
uniform sampler2D texture1;//take pixel color from the image

void main()
{
	//fs_color = vec4(vs_color, 1.f);//set color with no thransparency
	//fs_color = texture(texture0, vs_texcoord) /*set texture at background*/ * vec4(vs_color, 1.f); /*set color background*/
	fs_color = texture(texture1, vs_texcoord) * texture(texture0, vs_texcoord) * vec4(vs_color, 1.f);
} 