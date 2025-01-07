#version 330 core
in vec3 aPos;
in vec3 aCol;
in vec2 uv;
in vec3 aNormal;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPos;
uniform mat4 modelMatrix;
uniform mat4 transform;
uniform mat3 normalMatrix;
out vec2 UV;
out vec3 normal;
out vec3 modelPos;
out vec3 colour;
void main(){
	vec4 Position=vec4(aPos,1.0);
	Position=transform*modelMatrix*Position;
	modelPos=Position.xyz;
	gl_Position=projectionMatrix*viewMatrix*Position;
	//gl_Position=Position;
	//colour=aCol*(sin(time)+1)/2;
	UV=uv;
	normal=normalMatrix*aNormal;
};