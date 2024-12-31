#version 460 core
out vec4 FragColor;
in vec2 UV;
in vec3 normal;
in vec3 modelPos;
in vec3 colour;
uniform float time;
uniform sampler2D sampler;
uniform vec3 lightvec;
uniform vec3 lightCol;
uniform vec3 cameraPos;

//uniform sampler2D sampler1;
//uniform sampler2D sampler2;
void main(){
	//FragColor1=vec4(UV,0.0f,1.0f);
	//float intensity=(cos(time)+1)/2;
	//FragColor1=vec4(colour+vec3(intensity),1.0);
	//vec4 grassColor=
	//vec4 landColor=texture(sampler1,UV);
	//vec4 noiseColor=texture(sampler2,UV);
	//FragColor=texture(sampler,UV);//mix(grassColor,landColor,noiseColor.r);
	vec3 object_color=texture(sampler,UV).xyz;
	vec3 nor=normalize(normal);


	//vec3 col=lightCol*clamp(dot(nor,-lightvec),0.0,1.0)*clamp(dot(lightRef,viewDir),0.0,1.0)*object_color;
	vec3 col=lightCol*clamp(dot(nor,-lightvec),0.0,1.0)*object_color;
	FragColor=vec4(col,1.0);

	//vec3 viewDir=normalize(cameraPos-modelPos);
	//viewDir=clamp(viewDir,0.0,1.0);
	//vec3 lightRef=normalize(reflect(lightvec,nor));
	//FragColor=vec4(viewDir,1.0);

};