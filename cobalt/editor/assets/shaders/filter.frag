#version 410 core

out vec4 color;

in vec2 v_tex_coords;

uniform int u_targetWidth;
uniform int u_targetHeight;

uniform sampler2D u_source_scene;


void main() {
    // Sample the scene rendered texture
    vec4 texcolor = texture(u_source_scene, v_tex_coords);

    // Apply gamma correction
    color = vec4(pow(texcolor.rgb, vec3(1.0/2.2)), 1.0);
}