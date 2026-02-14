#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "ECS/TransformComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

using Catch::Matchers::WithinAbs;

TEST_CASE("Default transform is identity") {
    TransformComponent t;
    glm::mat4 local = t.getLocalMatrix();
    glm::mat4 identity = glm::mat4(1.0f);

    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            REQUIRE_THAT(local[col][row], WithinAbs(identity[col][row], 0.0001));
        }
    }
}

TEST_CASE("Translation affects local matrix") {
    TransformComponent t(glm::vec3(5.0f, 3.0f, -2.0f));
    glm::mat4 local = t.getLocalMatrix();

    REQUIRE_THAT(local[3][0], WithinAbs(5.0f, 0.0001));
    REQUIRE_THAT(local[3][1], WithinAbs(3.0f, 0.0001));
    REQUIRE_THAT(local[3][2], WithinAbs(-2.0f, 0.0001));
}

TEST_CASE("Scale affects local matrix") {
    TransformComponent t(glm::vec3(0.0f), glm::quat(1, 0, 0, 0), glm::vec3(2.0f, 3.0f, 4.0f));
    glm::mat4 local = t.getLocalMatrix();

    REQUIRE_THAT(local[0][0], WithinAbs(2.0f, 0.0001));
    REQUIRE_THAT(local[1][1], WithinAbs(3.0f, 0.0001));
    REQUIRE_THAT(local[2][2], WithinAbs(4.0f, 0.0001));
}

TEST_CASE("World matrix without parent equals local matrix") {
    TransformComponent t(glm::vec3(1.0f, 2.0f, 3.0f));
    glm::mat4 local = t.getLocalMatrix();
    glm::mat4 world = t.getWorldMatrix();

    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            REQUIRE_THAT(world[col][row], WithinAbs(local[col][row], 0.0001));
        }
    }
}

TEST_CASE("World matrix with parent combines transforms") {
    auto parent = std::make_shared<TransformComponent>(glm::vec3(10.0f, 0.0f, 0.0f));
    TransformComponent child(glm::vec3(0.0f, 5.0f, 0.0f));
    child.parent = parent;

    glm::mat4 world = child.getWorldMatrix();

    REQUIRE_THAT(world[3][0], WithinAbs(10.0f, 0.0001));
    REQUIRE_THAT(world[3][1], WithinAbs(5.0f, 0.0001));
    REQUIRE_THAT(world[3][2], WithinAbs(0.0f, 0.0001));
}

TEST_CASE("World matrix with grandparent") {
    auto grandparent = std::make_shared<TransformComponent>(glm::vec3(1.0f, 0.0f, 0.0f));
    auto parent = std::make_shared<TransformComponent>(glm::vec3(0.0f, 2.0f, 0.0f));
    parent->parent = grandparent;

    TransformComponent child(glm::vec3(0.0f, 0.0f, 3.0f));
    child.parent = parent;

    glm::mat4 world = child.getWorldMatrix();

    REQUIRE_THAT(world[3][0], WithinAbs(1.0f, 0.0001));
    REQUIRE_THAT(world[3][1], WithinAbs(2.0f, 0.0001));
    REQUIRE_THAT(world[3][2], WithinAbs(3.0f, 0.0001));
}

TEST_CASE("Expired parent is treated as no parent") {
    TransformComponent child(glm::vec3(0.0f, 5.0f, 0.0f));

    {
        auto parent = std::make_shared<TransformComponent>(glm::vec3(10.0f, 0.0f, 0.0f));
        child.parent = parent;
    } // parent destroyed here

    glm::mat4 world = child.getWorldMatrix();

    // Should behave as if no parent
    REQUIRE_THAT(world[3][0], WithinAbs(0.0f, 0.0001));
    REQUIRE_THAT(world[3][1], WithinAbs(5.0f, 0.0001));
}

TEST_CASE("90 degree rotation around Y axis") {
    glm::quat rot = glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    TransformComponent t(glm::vec3(0.0f), rot, glm::vec3(1.0f));
    glm::mat4 local = t.getLocalMatrix();

    // After 90 deg Y rotation: X axis should point along -Z
    REQUIRE_THAT(local[0][0], WithinAbs(0.0f, 0.0001));
    REQUIRE_THAT(local[0][2], WithinAbs(-1.0f, 0.0001));
}

TEST_CASE("Parent scale affects child world position") {
    auto parent = std::make_shared<TransformComponent>(
        glm::vec3(0.0f), glm::quat(1, 0, 0, 0), glm::vec3(2.0f)
    );
    TransformComponent child(glm::vec3(5.0f, 0.0f, 0.0f));
    child.parent = parent;

    glm::mat4 world = child.getWorldMatrix();

    // Child at local (5,0,0) with parent scaled 2x should be at world (10,0,0)
    REQUIRE_THAT(world[3][0], WithinAbs(10.0f, 0.0001));
}
