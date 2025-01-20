#pragma once
#include"material/material.h"
class WhiteMaterial:public Material
{
public:
    WhiteMaterial();
    ~WhiteMaterial(); 
    static std::shared_ptr<QOpenGLShaderProgram> getShaderProgram();
private:
    static std::once_flag shader_program_flag_;


};
