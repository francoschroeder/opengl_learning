#version 330 core
in vec2 TexCoord;
out vec4 color;

uniform sampler2D ourTexture;
uniform sampler2D faceTexture;
uniform float opacity;

void main() {
    vec4 containerTexture = texture(ourTexture, (TexCoord - vec2(-0.5, -0.5)) * 0.5);
    vec4 smileTexture = texture(faceTexture, vec2(-TexCoord.x, TexCoord.y) * 2);

    color = mix(containerTexture, smileTexture, opacity);
}
