#version 460 core
out vec4 FragColor;
in vec2 UV;
in vec3 normal;
in vec3 modelPos;
in vec3 colour;
uniform float specularIntensity;
uniform sampler2D sampler;
uniform sampler2D specular_map;
uniform vec3 lightvec;
uniform vec3 lightCol;
uniform vec3 cameraPos;
uniform vec3 ambientColor;
uniform vec3 lightPosition;
//uniform sampler2D sampler1;
//uniform sampler2D sampler2;
uniform float k1;
uniform float k2;
uniform float kc;
void main(){
	//FragColor1=vec4(UV,0.0f,1.0f);
	//float intensity=(cos(time)+1)/2;
	//FragColor1=vec4(colour+vec3(intensity),1.0);
	//vec4 grassColor=
	//vec4 landColor=texture(sampler1,UV);
	//vec4 noiseColor=texture(sampler2,UV);
	//FragColor=texture(sampler,UV);//mix(grassColor,landColor,noiseColor.r);
	vec3 object_color=texture(sampler,UV).xyz;
	vec3 normalN=normalize(normal);
	//vec3 lightDirN=normalize(lightvec);
	vec3 lightDirN=normalize(modelPos-lightPosition);	//光照方向
	float dist =length(modelPos-lightPosition);			//光源距离
	float attenuation=1.0/(kc+k1*dist+k2*dist*dist);	//缩减系数

	vec3 viewDir=normalize(cameraPos-modelPos);

	float diffuse=clamp(dot(-lightDirN,normalN),0.0,1.0);
	vec3 diffuseColor=lightCol*diffuse*object_color;	//物体漫反射光

	float dotResult=dot(normalN,-lightDirN);
	float flag=step(0.0,dotResult);					//入射光在背面过来时，夹角大于90度，不产生反射光

	vec3 lightReflect=normalize(reflect(lightDirN,normalN));	//Phong光照模型
	float specular=max(dot(lightReflect,viewDir),0.0);

	//vec3 halfwayDir =normalize(lightDirN+viewDir);			//Blinn-Phong光照，在相机与光源在法线同侧时仍然有效
	//float specular=max(dot(halfwayDir,normalN),0);

	specular=pow(specular,64);						//光斑大小
	float specularMask=texture(specular_map,UV).r;
	vec3 specularColor=specular*lightCol*object_color*specularIntensity*specularMask*flag;		//镜面反射光
	
	vec3 object_ambientColor=object_color*ambientColor;		//环境光
	vec3 finalColor=(diffuseColor+specularColor)*attenuation+object_ambientColor;
	FragColor=vec4(finalColor,1.0);

};