#include <GLFW/glfw3.h>
#include <cstdio>

int main() {
    // initialize GLFW
    if (!glfwInit()){
        printf("GLFW initialization failed\n");
        return -1;
    }

    /// TODO: add a higher version option for other platforms
    // ask for OpenGLCore 4.1, max on macOS
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // must be set for macOS

    // create the actual window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Scene Editor", nullptr, nullptr);
    if (!window) {
        printf("GLFW Window creation failed\n");
        glfwTerminate();
        return -1;
    }
    // setup GL context
    glfwMakeContextCurrent(window);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Clear the screen to dark gray
        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}
