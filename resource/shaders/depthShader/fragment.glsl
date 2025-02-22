#version 460 core
out vec4 FragColor;
uniform float near;
uniform float far;
void main()
{
	float zNdc=gl_FragCoord.z*2.0-1.0;
	float lineDepth=2.0*near/(far+near-zNdc*(far-near));
	FragColor=vec4(lineDepth,lineDepth,lineDepth,1.0f);
}