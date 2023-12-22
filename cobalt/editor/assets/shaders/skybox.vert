#version 410 core

layout(location = 0) in vec3 position;

out vec3 v_tex_coords;

uniform mat4 u_view;
uniform mat4 u_projection;


void main() {
    v_tex_coords = position;
    gl_Position = (u_projection * u_view * vec4(position, 1.0)).xyww;
}