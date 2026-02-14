#include <glm/gtc/matrix_transform.hpp>  // for translate, scale
#include <glm/gtc/quaternion.hpp>         // for mat4_cast
#include "TransformComponent.h"

glm::mat4 TransformComponent::getLocalMatrix() const {
    const glm::mat4 T = glm::translate(glm::mat4(1.0) , position);
    const glm::mat4 R = glm::mat4_cast(rotation);
    const glm::mat4 S = glm::scale(glm::mat4(1.0) , scale);
    return T * R * S;
}

glm::mat4 TransformComponent::getWorldMatrix() const {
    if (const auto parentPtr = parent.lock()) {
        return parentPtr->getWorldMatrix() * getLocalMatrix();
    }
    return getLocalMatrix();
}
