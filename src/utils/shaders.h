#include <glad/glad.h>
#include <iostream>
#include <vector>

GLuint createVertexShader(const GLchar* shader);
GLuint createFragmentShader(const GLchar* shader);
GLuint createShaderProgram(std::vector<GLuint> shaders);
