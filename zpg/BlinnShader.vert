#version 400 core
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 worldPos;
out vec3 worldNor;

void main() {
    vec4 worldPosition = uModel * vec4(vp, 1.0);
    worldPos = worldPosition.xyz;
    worldNor = mat3(transpose(inverse(uModel))) * vn;
    gl_Position = uProjection * uView * worldPosition;
}