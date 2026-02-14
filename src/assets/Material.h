#pragma once
#include <memory>
#include <string>
#include "Texture.h"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

struct Material {
    std::string name;
    glm::vec4 diffuseColor = {1.0f, 1.0f, 1.0f, 1.0f};
    glm::vec2 tiling = {1.0f, 1.0f};
    std::shared_ptr<Texture> diffuseTexture = nullptr;
};
