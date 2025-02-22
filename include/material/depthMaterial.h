#pragma once
#include"material/material.h"

class DepthMaterial : public Material
{
public:
	DepthMaterial();
	~DepthMaterial();
	static std::shared_ptr<QOpenGLShaderProgram> getShaderProgram();


private:
	static std::once_flag shader_program_flag_;

};