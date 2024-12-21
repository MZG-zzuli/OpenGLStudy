#version 330 core
in layout(location = 0) vec3 aPos;
void main(){
	//vec4 Position=vec4(aPos,1.0);
	//gl_Position=perspectiveMatrix*viewMatrix*Position;
	gl_Position=vec4(aPos,1.0);
	//colour=aCol*(sin(time)+1)/2;
	//UV=uv;
};