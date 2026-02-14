#pragma once
#include "Component.h"
#include "glm/vec3.hpp"

enum class LightType {
    Directional,
    Point,
    Spot
};

class LightComponent : public ComponentBase<LightComponent> {
    public:
    LightType lightType;
    glm::vec3 color = glm::vec3(1.0f);
    float intensity = 1.0f;
    float range = 10.0f;
    float attenuation = 2.0f;
    float innerConeAngle = 12.5f;
    float outerConeAngle = 45.0f;
    explicit LightComponent(const LightType type) : lightType(type) {}
    ~LightComponent() override = default;
};