#version 330 core
out vec4 fragColor;
uniform vec4 uObjectColor;

void main() {
    fragColor = uObjectColor;
}