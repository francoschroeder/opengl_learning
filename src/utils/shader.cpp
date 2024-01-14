#include "shader.h"
#include "shaders.h"

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::ifstream vertexFile, fragmentFile;
    std::stringstream vertexStream, fragmentStream;

    vertexFile.exceptions   (std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);

        vertexStream      << vertexFile.rdbuf();
        fragmentStream    << fragmentFile.rdbuf();

        vertexFile.close();
        fragmentFile.close();

    } catch (std::ifstream::failure exc) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    std::string vertexString    = vertexStream.str();
    std::string fragmentString  = fragmentStream.str();
    const char* vertexCode      = vertexString.c_str();
    const char* fragmentCode    = fragmentString.c_str();

    GLuint vertexShader = createVertexShader(vertexCode);
    GLuint fragmentShader = createFragmentShader(fragmentCode);
    std::vector<GLuint> shaders { vertexShader, fragmentShader };
    
    ID = createShaderProgram(shaders);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string name, bool value) {
    glUniform1i(glGetUniformLocation(ID, (const GLchar*) name.c_str()), (int) value);
}

void Shader::setInt(const std::string name, int value) {
    glUniform1i(glGetUniformLocation(ID, (const GLchar*) name.c_str()), value);
}

void Shader::setFloat(const std::string name, float value) {
    glUniform1f(glGetUniformLocation(ID, (const GLchar*) name.c_str()), value);
}
