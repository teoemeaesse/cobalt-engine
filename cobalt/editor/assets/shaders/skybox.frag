#version 430 core

out vec4 color;

in vec3 v_tex_coords;

uniform samplerCube u_skybox;


void main() {
    color = texture(u_skybox, -normalize(v_tex_coords));
}