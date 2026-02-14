#pragma once
#include <memory>

#include "Component.h"
#include "glm/fwd.hpp"
#include "glm/gtc/quaternion.hpp"

class TransformComponent : public ComponentBase<TransformComponent> {
    public:
    std::weak_ptr<TransformComponent> parent;
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    explicit TransformComponent(
    const glm::vec3& pos = glm::vec3(0.0f),
    const glm::quat& rot = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
    const glm::vec3& scl = glm::vec3(1.0f)
    ) : position(pos), rotation(rot), scale(scl) {}

    ~TransformComponent() override = default;

    [[nodiscard]] glm::mat4 getLocalMatrix() const;
    [[nodiscard]] glm::mat4 getWorldMatrix() const;

};
