#pragma once


#include<memory>
#include"object.h"
#include"geometry.h"
#include"material/material.h"
class Mesh :public Object
{
public:
	Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material>material);
	~Mesh();
	std::shared_ptr<Geometry> getGeometry() const;
	std::shared_ptr<Material> getMaterial() const;
private:
	std::shared_ptr<Geometry> geometry_;
	std::shared_ptr<Material> material_;

};