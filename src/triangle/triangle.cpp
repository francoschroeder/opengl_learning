#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../utils/window.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

const char* vertexShaderSource = ""
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;"

    "void main() {"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
    "}";

const char* fragmentShaderSource = ""
    "#version 330 core\n"
    "out vec4 FragColor;"

    "void main() {"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
    "}";

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

GLuint createVertexShader() {
    GLuint vertexShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        return 0;
    }

    return vertexShader;
}

GLuint createFragmentShader() {
    GLuint fragmentShader;

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

        return 0;
    }

    return fragmentShader;
}

GLuint createShaderProgram(GLuint shaders[], int shaderCount) {
    GLuint shaderProgram;

    shaderProgram = glCreateProgram();

    for (int i = 0; i <= shaderCount - 1; i++) {
        glAttachShader(shaderProgram, shaders[i]);
    }

    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    return shaderProgram;
}

int main() {
    GLFWwindow* window = createWindow(SCREEN_WIDTH, SCREEN_HEIGHT); 

    if (window == NULL) {
        return ERROR;
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    float triangleVertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 1
    };

    

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW); 
    
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint vertexShader = createVertexShader();

    if (vertexShader == 0) {
        return ERROR;
    }

    GLuint fragmentShader = createFragmentShader();

    if (fragmentShader == 0) {
        return ERROR;
    }

    GLuint shaderArray[] = { vertexShader, fragmentShader };
    GLuint shaderProgram = createShaderProgram(shaderArray, 2);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return SUCCESS;
}
