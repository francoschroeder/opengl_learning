#version 330 core
layout (location = 0) in vec2 pos;
out vec3 positionOut;

uniform float turningDegree;
uniform float horizontalOffset;

void main() {
    positionOut = vec3(pos.x * turningDegree + horizontalOffset, pos.y, 0.0f);
    gl_Position = vec4(positionOut, 1.0f);
}
