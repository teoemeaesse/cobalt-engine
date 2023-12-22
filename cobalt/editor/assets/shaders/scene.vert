#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex_coords;
layout(location = 2) in vec3 normal;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_model;
uniform mat3 u_normal_matrix;

out vec3 v_world_position;
out vec2 v_tex_coords;
out vec3 v_normal;


void main() {
    v_world_position = vec3(u_model * vec4(position, 1.0));
    v_tex_coords = tex_coords;
    v_normal = normalize(u_normal_matrix * normal);
    gl_Position = u_projection * u_view * vec4(v_world_position, 1.0);
}