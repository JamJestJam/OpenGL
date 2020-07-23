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

vec3 CalculateAmbient(){
	return material.ambient;
}//calc ambient light
vec3 CalculateDifuse(){
	vec3 posToLightDirVec = normalize(vs_position - LightPos0);
	float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
	return material.diffuse * diffuse;
}//calc diffuse light
vec3 CalculateSpecular(){
	vec3 lightToPosDirVer = normalize(LightPos0 - vs_position);
	vec3 reflectDirVec = normalize(reflect(lightToPosDirVer, normalize(vs_normal)));
	vec3 posToViewDirVec = normalize(vs_position - CameraPos);
	float specularConstent = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
	return material.specular * specularConstent;
}//calc specular light 

void main()
{
	//Ambient light - how object shines
	vec3 ambientFinal = CalculateAmbient();

	//Diffuse light - how object reflect light
	vec3 diffuseFinal = CalculateDifuse();

	//Specular light - flare
	vec3 specularFinal = CalculateSpecular();

	//Attenuation

	//mix together
	fs_color = 
		texture(material.diffuseTex, vs_texcoord) *					//texture0
		texture(material.specularTex, vs_texcoord) *				//texture1
		vec4(vs_color, 1.f) *										//vertex color
		(
			vec4(ambientFinal, 1.f) +								//Ambient
			vec4(diffuseFinal, 1.f) +								//Diffuse
			vec4(specularFinal, 1.f)								//Specular
		);			
} 