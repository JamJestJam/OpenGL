#version 440

//inform graphic card about data in pipeline
in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

//inform graphic card about data out from pipeline
out vec4 fs_color;

uniform sampler2D texture0;//take pixel color from the image
uniform sampler2D texture1;//take pixel color from the image

uniform vec3 LightPos0;//position of light

void main()
{
	//fs_color = vec4(vs_color, 1.f);//set color with no thransparency
	//fs_color = texture(texture1, vs_texcoord) /*set texture at background*/ * vec4(vs_color, 1.f); /*set color background*/

	//Ambient light
	vec3 ambientLight = vec3(0.01f, 0.01f, 0.01f);

	//Diffuse light
	vec3 posToLightDirVec = normalize(vs_position - LightPos0);
	vec3 diffuseColor = vec3(1.f, 1.f, 1.f);
	float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	vec3 diffuseFinal = diffuseColor * diffuse;

	//mix together
	fs_color = texture(texture0, vs_texcoord) *							//texture0
				vec4(vs_color, 1.f) *									//vertex color
				(vec4(ambientLight, 1.f) + vec4(diffuseFinal, 1.f));	//light

} 