#include"mesh.h"

Mesh::Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material):
    geometry_(geometry),
    material_(material)
{
    type_ = ObjectType::Mesh;
}

Mesh::~Mesh()
{
}

std::shared_ptr<Geometry> Mesh::getGeometry() const
{
    return geometry_;
}

std::shared_ptr<Material> Mesh::getMaterial() const
{
    return material_;
}
