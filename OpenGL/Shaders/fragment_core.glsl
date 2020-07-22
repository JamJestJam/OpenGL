#version 440

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	sampler2D diffuseTex;
	sampler2D specularTex;
};

//inform graphic card about data in pipeline
in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

//inform graphic card about data out from pipeline
out vec4 fs_color;

uniform Material material;//take material options

uniform vec3 LightPos0;//position of light
uniform vec3 CameraPos;//position of camera

void main()
{
	//Ambient light - eternal light
	vec3 ambientLight = material.ambient;

	//Diffuse light - light given
	vec3 posToLightDirVec = normalize(vs_position - LightPos0);
	float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	vec3 diffuseFinal = material.diffuse * diffuse;

	//Specular light - reflected light
	vec3 lightToPosDirVer = normalize(LightPos0 - vs_position);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVer, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(vs_position - CameraPos);
	float specularConstent = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
	vec3 specularFinal = material.specular * specularConstent;

	//Attenuation

	//mix together
	fs_color = 
			texture(material.diffuseTex, vs_texcoord) *							//texture0
			texture(material.specularTex, vs_texcoord) *							//texture1
			vec4(vs_color, 1.f) *										//vertex color
			(
				vec4(ambientLight, 1.f) +								//Ambient
				vec4(diffuseFinal, 1.f) +								//Diffuse
				vec4(specularFinal, 1.f)								//Specular
			);			
	
} 