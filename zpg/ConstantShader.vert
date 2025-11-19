#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTextCoord;

out vec2 textCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform bool hasTextCoord = true;

void main()
{
    if (hasTextCoord)
        textCoord = aTextCoord;
    else
        textCoord = vec2(0.0);

    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}
