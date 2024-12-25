#version 330 core
in vec3 aPos;
in vec3 aCol;
in vec2 uv;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec2 UV;
out vec3 colour;
void main(){
	vec4 Position=vec4(aPos,1.0);
	gl_Position=projectionMatrix*viewMatrix*Position;
	//gl_Position=Position;
	//colour=aCol*(sin(time)+1)/2;
	UV=uv;
};