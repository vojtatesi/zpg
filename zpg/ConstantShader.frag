#version 330 core

in vec2 textCoord;
out vec4 fragColor;

uniform sampler2D uTexture;
uniform vec4 uObjectColor;
uniform bool useTexture = false;
uniform float uTexScale = 1.0;

void main()
{
    vec2 tiledUV = textCoord * uTexScale;
    if (useTexture)
        fragColor = texture(uTexture, tiledUV) * uObjectColor;
    else
        fragColor = uObjectColor;
}