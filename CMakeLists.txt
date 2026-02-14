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

add_executable(SceneEditor src/main.cpp ${IMGUI_SOURCES})

# Include paths
target_include_directories(SceneEditor PRIVATE
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)

# Link libraries
target_link_libraries(SceneEditor PRIVATE glfw glm OpenGL::GL)