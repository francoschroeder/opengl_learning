#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "../utils/shader.h"
#include "../utils/shaders.h"
#include "../utils/window.h"

const unsigned int SCREEN_HEIGHT    = 800;
const unsigned int SCREEN_WIDTH     = 600;

const GLfloat triangle[] = {
    -0.5f, -0.5f,
    0.0f, 0.5f,
    0.5f, -0.5f
};

int main() {
    GLFWwindow* window = createWindow(SCREEN_HEIGHT, SCREEN_WIDTH);

    if (window == NULL) {
        return ERROR;
    }

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);

    Shader shader("src/chapterShaders/vertexShader.vert", "src/chapterShaders/fragmentShader.frag"); 

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        shader.setFloat("turningDegree", sin(glfwGetTime()));
        shader.setFloat("horizontalOffset", sin(glfwGetTime()));

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return SUCCESS;
}
