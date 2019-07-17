#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 pv; // projection * view

out vec3 Normal;
out vec2 TexCoords;

void main() {
    TexCoords = aTexCoords;
    Normal = aNormal;
    
    gl_Position = pv * model * vec4(aPos, 1.0f);
}
