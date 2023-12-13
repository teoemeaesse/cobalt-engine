#version 430 core

out vec4 color;

in vec2 v_tex_coords;

uniform int u_targetWidth;
uniform int u_targetHeight;

uniform sampler2D u_source_scene;


void main() {
    color = texture(u_source_scene, v_tex_coords);
    
}