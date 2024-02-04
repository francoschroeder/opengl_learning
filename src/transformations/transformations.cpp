#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

#include "../utils/window.h"
#include "../utils/shader.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const GLfloat triangle[] = {
    //Vertex       //Color
    -0.5f, -0.5,   1, 0, 0,
    0, 0.5f,       0, 1, 0,
    0.5f, -0.5f,   0, 0, 1
};

int main() {
    GLFWwindow* window = createWindow(WINDOW_WIDTH, WINDOW_HEIGHT);

    if (window == NULL) {
        return ERROR;
    }

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *) (2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    Shader shader = Shader("src/transformations/vertexShader.vert", "src/transformations/fragmentShader.frag");
    GLuint transUniformId = glGetUniformLocation(shader.ID, "transMatrix");

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        glm::mat4 trans = glm::mat4(1);
        trans = glm::translate(trans, glm::vec3(0.5, 0.5, 0));
        trans = glm::rotate(trans, glm::radians((float) std::sin(glfwGetTime()) * 360), glm::vec3(0, 0, 1));
        
        glUniformMatrix4fv(transUniformId, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return SUCCESS;
}
