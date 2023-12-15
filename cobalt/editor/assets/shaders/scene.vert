#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex_coords;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model;

out vec3 v_world_position;
out vec2 v_tex_coords;


void main() {
    v_world_position = (u_model * vec4(position, 1.0)).xyz;
    v_tex_coords = tex_coords;
    gl_Position = u_projection * u_view * u_model * vec4(position, 1.0);
}