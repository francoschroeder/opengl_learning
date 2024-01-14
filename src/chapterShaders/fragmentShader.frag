#version 330 core
in vec3 positionOut;

out vec4 FragColor;

void main() {
    FragColor = vec4(positionOut, 1.0f);
}
