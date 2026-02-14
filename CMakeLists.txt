cmake_minimum_required(VERSION 4.1)
project(SceneEditor)

set(CMAKE_CXX_STANDARD 20)

# GLFW - windowing and input
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory(extern/glfw)

# GLM - math library
add_subdirectory(extern/glm)

# ImGui
set(IMGUI_DIR extern/imgui)
set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# OpenGL - required for MacOS
find_package(OpenGL REQUIRED)

# Silence macOS OpenGL deprecation warnings
add_definitions(-DGL_SILENCE_DEPRECATION)

set(ECS_DIR src/ECS)
set(ECS_SOURCES
        ${ECS_DIR}/TransformComponent.cpp
        ${ECS_DIR}/CameraComponent.cpp
)

add_executable(SceneEditor src/main.cpp ${ECS_SOURCES} ${IMGUI_SOURCES})

# Include paths
target_include_directories(SceneEditor PRIVATE
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        src
)

# Link libraries
target_link_libraries(SceneEditor PRIVATE glfw glm OpenGL::GL)

# Testing
set(TEST_DIR tests)
set(TEST_SOURCES
        ${TEST_DIR}/test_ecs.cpp
        ${TEST_DIR}/test_transforms.cpp
)


add_subdirectory(extern/Catch2)
add_executable(SceneEditorTests ${TEST_SOURCES} ${ECS_SOURCES})
target_link_libraries(SceneEditorTests PRIVATE Catch2::Catch2WithMain glm)
target_include_directories(SceneEditorTests PRIVATE src)