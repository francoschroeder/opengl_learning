#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "window.h"

const unsigned int OPEN_GL_MAJOR_VERSION = 3;
const unsigned int OPEN_GL_MINOR_VERSION = 3;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* createWindow(int width, int height, const char* title) {
    GLFWwindow* window;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPEN_GL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPEN_GL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to initialize window" << std::endl;
        glfwTerminate();

        return NULL;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;

        return NULL;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}
