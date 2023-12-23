#version 410 core

out vec4 color;

in vec2 v_tex_coords;

uniform int u_targetWidth;
uniform int u_targetHeight;

uniform sampler2D u_source_scene;

const float exposure = 1.0;
const float gamma = 2.2;

void main() {
    // Sample the scene rendered texture
    vec3 hdrColor = texture(u_source_scene, v_tex_coords).rgb;

    // Apply gamma correction + tone mapping
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
    mapped = pow(mapped, vec3(1.0 / gamma));
    color = vec4(mapped, 1.0);
}