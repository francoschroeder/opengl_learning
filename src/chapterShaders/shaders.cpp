#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cmath>

#include "../utils/window.h"
#include "../utils/shaders.h"

const unsigned int SCREEN_WIDTH     = 800;
const unsigned int SCREEN_HEIGHT    = 600;

const GLchar* vertexShaderSource = ""
    "#version 330 core\n"
    "layout (location = 0) in vec2 pos;"
    "layout (location = 1) in vec3 color;"
    "out vec3 colorOut;"

    "void main() {"
        "gl_Position = vec4(pos, 0.0, 1.0);"
        "colorOut = color;"
    "}";

const GLchar* fragmentShaderSource = ""
    "#version 330 core\n"
    "in vec3 colorOut;"
    "out vec4 FragColor;"

    "void main() {"
        "FragColor = vec4(colorOut, 1.0f);"
    "}";

int main() {
    GLFWwindow* window = createWindow(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (window == NULL) {
        return ERROR;
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    const GLfloat triangle[] = {
        -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) (2 * (sizeof(GLfloat))));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    GLuint vertexShader = createVertexShader(vertexShaderSource);
    GLuint fragmentShader = createFragmentShader(fragmentShaderSource);

    std::vector<GLuint> shaders { vertexShader, fragmentShader };
    
    GLuint shaderProgram = createShaderProgram(shaders);

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return SUCCESS;
}
