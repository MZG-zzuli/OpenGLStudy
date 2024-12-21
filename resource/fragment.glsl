#version 460 core
out vec4 FragColor1;
in vec3 colour;
in vec2 UV;
uniform float time;
uniform sampler2D sampler;
//uniform sampler2D sampler1;
//uniform sampler2D sampler2;
void main(){
	//FragColor1=vec4(UV,0.0f,1.0f);
	//float intensity=(cos(time)+1)/2;
	//FragColor1=vec4(colour+vec3(intensity),1.0);
	//vec4 grassColor=
	//vec4 landColor=texture(sampler1,UV);
	//vec4 noiseColor=texture(sampler2,UV);
	FragColor1=texture(sampler,UV);//mix(grassColor,landColor,noiseColor.r);

};