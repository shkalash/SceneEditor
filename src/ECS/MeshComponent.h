#pragma once
#include <memory>

#include "Component.h"

// Forward declare the dependencies.
// Mostly irrelevant on this project scale at the moment, but good practice for future-proofing and scaling later
class Material;
class Mesh;

class MeshComponent : public ComponentBase<MeshComponent> {
    public:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;

    MeshComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
    : mesh(std::move(mesh)), material(std::move(material)) {}

    ~MeshComponent() override = default;
};
