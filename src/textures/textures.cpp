#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "../utils/shader.h"
#include "../utils/shaders.h"
#include "../utils/window.h"
#include "../include/stb/stb_image.h"

const unsigned int SCREEN_HEIGHT    = 800;
const unsigned int SCREEN_WIDTH     = 600;

const GLfloat rectangle[] = {
    -0.5f, -0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 1.0f, 
    0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 1.0f, 0.0f
};

const GLuint indices[] = {
    0, 1, 2,
    0, 2, 3
};

float opacity = 0.2f;

void upDownCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        if (opacity + 0.05f <= 1.0f) {
            opacity += 0.05f;
        }
    }

    if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        if (opacity - 0.05f >= 0.0f) {
            opacity -= 0.05f;
        }
    }
}

int main() {
    GLFWwindow* window = createWindow(SCREEN_HEIGHT, SCREEN_WIDTH);

    if (window == NULL) {
        return ERROR;
    }

    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *) 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *) (2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("src/textures/container.jpg", &width, &height, &nrChannels, 0);

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    GLuint faceTexture;
    glGenTextures(1, &faceTexture);
    glBindTexture(GL_TEXTURE_2D, faceTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("src/textures/awesomeface.png", &width, &height, &nrChannels, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    Shader shader("src/textures/vertexShader.vert", "src/textures/fragmentShader.frag"); 

    shader.use();
    shader.setInt("ourTexture", 0);
    shader.setInt("faceTexture", 1);

    glfwSetKeyCallback(window, upDownCallback);

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }


        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        std::cout << opacity << std::endl;
        shader.setFloat("opacity", opacity);
        glBindVertexArray(vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, faceTexture);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return SUCCESS;
}
