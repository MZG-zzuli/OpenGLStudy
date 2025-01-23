#version 460 core
out vec4 FragColor;
in vec2 UV;
in vec3 normal;
in vec3 modelPos;
//uniform float specularIntensity;
uniform sampler2D sampler;
uniform sampler2D specular_map;
//uniform vec3 targetDirection;
//uniform float innerAngle;		//弧度(内圈）
//uniform float outerAngle;		//弧度(外圈）
//uniform vec3 lightCol;
uniform vec3 cameraPos;
uniform vec3 ambientColor;
//uniform vec3 lightPosition;
//uniform sampler2D sampler1;
//uniform sampler2D sampler2;
uniform float k1;
uniform float k2;
uniform float kc;

struct PointLight
{
	float k1;
	float k2;
	float kc;
	vec3 position;
	float specular_intensity;
	vec3 color;
};

struct SpotLight
{
	vec3 position;
	vec3 targetDirection;
	vec3 color;
	float outerLine;		//弧度(外圈）
	float innerLine;		//弧度(内圈）
	float specular_intensity;
};

struct DirectionalLight
{
	vec3 direction;
	float specular_intensity;
	vec3 color;
};
#define DIRECTION_LIGHT_COUNT 2
uniform SpotLight spotLight;
uniform DirectionalLight directionalLights[DIRECTION_LIGHT_COUNT];

vec3 getDiffuseColor(vec3 lightColor,vec3 objectColor,vec3 lightDir,vec3 normal)
{
	float diffuse=clamp(dot(-lightDir,normal),0.0,1.0);
	return diffuse*lightColor*objectColor;
}
vec3 getSpecularColor(vec3 lightColor,vec3 objectColor,vec3 lightDir,vec3 normal,vec3 viewDir,float specularIntensity)
{
	float dotResult=dot(-lightDir,normal);
	float flag=step(0.0,dotResult);
	vec3 reflectDir=normalize(reflect(lightDir,normal));
	float specular=max(dot(reflectDir,-viewDir),0.0);
	specular=pow(specular,64);
	float specularMask=texture(specular_map,UV).r;
	return specular*flag*lightColor*objectColor*specularIntensity*specularMask;

}
vec3 getSpotLightColor(SpotLight spotLight,vec3 objectColor,vec3 normal,vec3 cameraPos)
{
	vec3 result=vec3(0.0);
	vec3 lightDir=normalize(modelPos-spotLight.position);
	vec3 viewDir=normalize(modelPos-cameraPos);
	result+=getDiffuseColor(spotLight.color,objectColor,lightDir,normal);
	result+=getSpecularColor(spotLight.color,objectColor,lightDir,normal,viewDir,spotLight.specular_intensity);
	result*=clamp((dot(lightDir,spotLight.targetDirection)-cos(spotLight.outerLine))/
						(cos(spotLight.innerLine)-cos(spotLight.outerLine)),0.0,1.0);
	return result;
}
vec3 getDirectionalLightColor(DirectionalLight directionalLight,vec3 objectColor,vec3 normal,vec3 cameraPos)
{
	vec3 result=vec3(0.0);
	vec3 viewDir=normalize(modelPos-cameraPos);
	result+=getDiffuseColor(directionalLight.color,objectColor,directionalLight.direction,normal);
	result+=getSpecularColor(directionalLight.color,objectColor,directionalLight.direction,normal,viewDir,directionalLight.specular_intensity);
	return result;
}
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
	//vec3 lightDirN=normalize(modelPos-spotLight.position);	//此处光照方向
	//float Visible=dot(lightDirN,spotLight.targetDirection);
	//float visible_flag=step(cos(visibleAngle),Visible);
	//float intensity=clamp((Visible-cos(spotLight.outerLine))/(cos(spotLight.innerLine)-cos(spotLight.outerLine)),0.0,1.0);
	//float dist =length(modelPos-spotLight.position);			//光源距离
	//float attenuation=1.0/(kc+k1*dist+k2*dist*dist);	//缩减系数

	//vec3 viewDir=normalize(cameraPos-modelPos);

	//float diffuse=clamp(dot(-lightDirN,normalN),0.0,1.0);
	//vec3 diffuseColor=spotLight.color*diffuse*object_color;	//物体漫反射光

	//float dotResult=dot(normalN,-lightDirN);
	//float flag=step(0.0,dotResult);					//入射光在背面过来时，夹角大于90度，不产生反射光

	//vec3 lightReflect=normalize(reflect(lightDirN,normalN));	//Phong光照模型,反射光方向
	//float specular=max(dot(lightReflect,viewDir),0.0);

	//vec3 halfwayDir =normalize(lightDirN+viewDir);			//Blinn-Phong光照，在相机与光源在法线同侧时仍然有效
	//float specular=max(dot(halfwayDir,normalN),0);

	//specular=pow(specular,64);						//光斑大小
	//float specularMask=texture(specular_map,UV).r;
	//vec3 specularColor=specular*spotLight.color*object_color*spotLight.specular_intensity*flag;		//镜面反射光
	
	vec3 object_ambientColor=object_color*ambientColor;		//环境光
	//vec3 finalColor=(diffuseColor+specularColor)*intensity+object_ambientColor;
	vec3 finalColor=object_ambientColor;
	finalColor+=getSpotLightColor(spotLight,object_color,normalN,cameraPos);
	for(int i=0;i<DIRECTION_LIGHT_COUNT;i++)
	{
		finalColor+=getDirectionalLightColor(directionalLights[i],object_color,normalN,cameraPos);
	}
	FragColor=vec4(finalColor,1.0);

};