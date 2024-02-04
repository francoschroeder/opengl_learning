#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 color;

uniform mat4 transMatrix;

out vec3 colorOut;

void main() {
    gl_Position = transMatrix * vec4(pos, 1, 1);
    colorOut = color;
}
