#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex_coords;
layout(location = 2) in vec3 normal;

out vec2 v_tex_coords;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model;


void main() {
    v_tex_coords = tex_coords;
    gl_Position = u_projection * u_view * u_model * vec4(position, 1.0);
}