#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "../utils/window.h"
#include "../utils/shaders.h"

const unsigned int SCREEN_WIDTH     = 800;
const unsigned int SCREEN_HEIGHT    = 600;

const GLfloat firstTriangle[] = {
    -0.5f, -0.25f, 0.0f,
    -0.25f, 0.25f, 0.0f,
    0.0f, -0.25f, 0.0f
};

const GLfloat secondTriangle[] = {
    0.0f, -0.25f, 0.0f,
    0.25f, 0.25f, 0.0f,
    0.5f, -0.25f, 0.0f
};

const char* vertexShaderSource = ""
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;"

    "void main() {"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
    "}";

const char* orangeFragmentShaderSource = ""
    "#version 330 core\n"
    "out vec4 FragColor;"

    "void main() {"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
    "}";

const char* yellowFragmentShaderSource = ""
    "#version 330 core\n"
    "out vec4 FragColor;"

    "void main() {"
        "FragColor = vec4(1.0f, 1.0f, 0.0f, 0.0f);"
    "}";

int main() {
    GLFWwindow* window = createWindow(SCREEN_WIDTH, SCREEN_HEIGHT);

    if (window == NULL) {
        return ERROR;
    }

    GLuint vao[2], vbo[2];
    
    //Create vertex array objects and vertex buffer objects
    glGenVertexArrays(2, vao);
    glGenBuffers(2, vbo);

    //Bind first triangle
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);

    //Bind second triangle
    glBindVertexArray(vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);

    //Shaders
    GLuint vertexShader;
    vertexShader = createVertexShader(vertexShaderSource);

    GLuint orangeFragmentShader;
    orangeFragmentShader = createFragmentShader(orangeFragmentShaderSource);

    GLuint yellowFragmentShader;
    yellowFragmentShader = createFragmentShader(yellowFragmentShaderSource);

    std::vector<GLuint> shadersFirstTriangle { vertexShader, orangeFragmentShader };
    GLuint firstTriangleShaderProgram = createShaderProgram(shadersFirstTriangle);
   
    std::vector<GLuint> shadersSecondTriangle { vertexShader, yellowFragmentShader };
    GLuint secondTriangleShaderProgram = createShaderProgram(shadersSecondTriangle);

    glDeleteShader(vertexShader);
    glDeleteShader(orangeFragmentShader);
    glDeleteShader(yellowFragmentShader);

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        glUseProgram(firstTriangleShaderProgram); 
        glBindVertexArray(vao[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(secondTriangleShaderProgram);
        glBindVertexArray(vao[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, vao);
    glDeleteBuffers(2, vbo);
    glDeleteProgram(firstTriangleShaderProgram);
    glDeleteProgram(secondTriangleShaderProgram);

    glfwTerminate();

    return SUCCESS;
}
