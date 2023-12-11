#version 430 core

out vec4 color;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model;

void main() {
    color = vec4(1.0, 0.0, 0.0, 1.0);
}