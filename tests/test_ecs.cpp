#include <catch2/catch_test_macros.hpp>
#include "ECS/Entity.h"
#include "ECS/LightComponent.h"
#include "ECS/CameraComponent.h"
#include "ECS/MeshComponent.h"
#include "ECS/TransformComponent.h"

TEST_CASE("Entity gets unique UUID") {
    Entity a("First");
    Entity b("Second");
    REQUIRE(a.uuid != b.uuid);
}

TEST_CASE("Entity stores name") {
    Entity entity("MyEntity");
    REQUIRE(entity.name == "MyEntity");
}

TEST_CASE("Add and retrieve component") {
    Entity entity("Test");
    entity.addComponent<LightComponent>(LightType::Point);

    auto* light = entity.getComponent<LightComponent>();
    REQUIRE(light != nullptr);
    REQUIRE(light->lightType == LightType::Point);
}

TEST_CASE("Get missing component returns nullptr") {
    Entity entity("Test");
    REQUIRE(entity.getComponent<CameraComponent>() == nullptr);
}

TEST_CASE("Remove component") {
    Entity entity("Test");
    entity.addComponent<LightComponent>(LightType::Spot);
    entity.removeComponent<LightComponent>();
    REQUIRE(entity.getComponent<LightComponent>() == nullptr);
}

TEST_CASE("Multiple components on one entity") {
    Entity entity("Multi");
    entity.addComponent<LightComponent>(LightType::Directional);
    entity.addComponent<CameraComponent>(ProjectionType::Perspective);
    entity.addComponent<TransformComponent>();

    REQUIRE(entity.getComponent<LightComponent>() != nullptr);
    REQUIRE(entity.getComponent<CameraComponent>() != nullptr);
    REQUIRE(entity.getComponent<TransformComponent>() != nullptr);
}

TEST_CASE("Remove one component doesnt affect others") {
    Entity entity("Test");
    entity.addComponent<LightComponent>(LightType::Point);
    entity.addComponent<CameraComponent>(ProjectionType::Orthographic);

    entity.removeComponent<LightComponent>();

    REQUIRE(entity.getComponent<LightComponent>() == nullptr);
    REQUIRE(entity.getComponent<CameraComponent>() != nullptr);
}

TEST_CASE("Component data is preserved") {
    Entity entity("Test");
    auto* light = entity.addComponent<LightComponent>(LightType::Spot);
    light->intensity = 5.0f;
    light->color = glm::vec3(1.0f, 0.0f, 0.0f);
    light->innerConeAngle = 20.0f;

    auto* retrieved = entity.getComponent<LightComponent>();
    REQUIRE(retrieved->intensity == 5.0f);
    REQUIRE(retrieved->color.r == 1.0f);
    REQUIRE(retrieved->color.g == 0.0f);
    REQUIRE(retrieved->innerConeAngle == 20.0f);
}

TEST_CASE("Component type IDs") {
    SECTION("are unique per type") {
        auto lightID = Component::getTypeId<LightComponent>();
        auto cameraID = Component::getTypeId<CameraComponent>();
        auto meshID = Component::getTypeId<MeshComponent>();
        auto transformID = Component::getTypeId<TransformComponent>();
        
        REQUIRE(lightID != cameraID);
        REQUIRE(lightID != meshID);
        REQUIRE(lightID != transformID);
        REQUIRE(cameraID != meshID);
        REQUIRE(cameraID != transformID);
        REQUIRE(meshID != transformID);
    }

    SECTION("are stable across calls") {
        auto first = Component::getTypeId<LightComponent>();
        auto second = Component::getTypeId<LightComponent>();
        REQUIRE(first == second);
    }
}

TEST_CASE("Camera component defaults") {
    Entity entity("CamEntity");
    auto* cam = entity.addComponent<CameraComponent>(ProjectionType::Perspective);
    REQUIRE(cam->fov == 60.0f);
    REQUIRE(cam->nearPlane == 0.1f);
    REQUIRE(cam->farPlane == 1000.0f);
}

TEST_CASE("Light component defaults") {
    Entity entity("LightEntity");
    auto* light = entity.addComponent<LightComponent>(LightType::Point);
    REQUIRE(light->intensity == 1.0f);
    REQUIRE(light->range == 10.0f);
    REQUIRE(light->color == glm::vec3(1.0f));
}
