#pragma once

#include<mutex>
#include<QOpenGLShaderProgram>
enum class MaterialType
{
    PhongMaterial,
    WhiteMaterial,
    DepthMaterial
};

class Material
{
public:
    Material();
    virtual ~Material();
    MaterialType getMaterialType() const;

    bool getEnableDepthTest() const;
    void setEnableDepthTest(bool enable_depth_test);
    GLboolean getEnableDepthMask() const;
    void setEnableDepthMask(GLboolean enable_depth_mask);
    GLenum getDepthFunc() const;
    void setDepthFunc(GLenum func);
    bool getEnablePolygonOffset() const;
    void setEnablePolygonOffset(bool enable_polygon_offset);
    GLenum getPolygonOffsetType() const;
    void setPolygonOffsetType(GLenum polygon_offset_type);
    GLfloat getPolygonOffsetFactor() const;
    void setPolygonOffsetFactor(GLfloat polygon_offset_factor);
    GLfloat getPolygonOffsetUnits() const;
    void setPolygonOffsetUnits(GLfloat polygon_offset_units);
protected:
    MaterialType type_;
private:
    bool enable_depth_test_{ true };    //是否启动深度测试
    GLboolean enable_depth_mask_{ GL_TRUE };    //是否启动深度写入
    GLenum depth_func_{ GL_LESS };
    bool enable_polygon_offset_{ false };
    GLenum polygon_offset_type_{ GL_POLYGON_OFFSET_FILL };
    GLfloat polygon_offset_factor_{ 1.0f };
    GLfloat polygon_offset_units_{ 0.0f };
};