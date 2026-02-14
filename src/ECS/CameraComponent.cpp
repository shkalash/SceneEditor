#include "CameraComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cassert>

glm::mat4 CameraComponent::getProjectionMatrix(const float aspectRatio) const {
    switch (projectionType) {
        case ProjectionType::Perspective:
            return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
        case ProjectionType::Orthographic: {
            const float halfHeight = orthographicScale * 0.5f;
            const float halfWidth = halfHeight * aspectRatio;
            return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane);
        }
    }
    assert(false && "Unknown projection type");
}