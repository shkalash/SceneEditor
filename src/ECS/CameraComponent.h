#pragma once
#include "Component.h"
#include "glm/fwd.hpp"

enum class ProjectionType {
    Perspective,
    Orthographic
};

class CameraComponent : public ComponentBase<CameraComponent> {
    public:
    ProjectionType projectionType;
    float fov = 60.0f;
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;
    float orthographicScale = 1.0f;

    explicit CameraComponent(ProjectionType type) : projectionType(type) {}
    ~CameraComponent() override = default;

    [[nodiscard]] glm::mat4 getProjectionMatrix(float aspectRatio) const;
};