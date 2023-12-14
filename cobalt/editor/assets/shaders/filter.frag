#version 430 core

out vec4 color;

in vec2 v_tex_coords;

uniform int u_targetWidth;
uniform int u_targetHeight;

uniform sampler2D u_source_scene;


void main() {
    vec2 uv = vec2(gl_FragCoord.x / u_targetWidth, gl_FragCoord.y / u_targetHeight);

    vec3 color_top = vec3(0.5, 0.7, 1.0);
    vec3 color_bottom = mix(color_top, vec3(1.0, 1.0, 1.0), 0.8);

    vec3 gradient_color = mix(color_bottom, color_top, sqrt(uv.y));

    color = vec4(gradient_color, 1.0);
    vec4 texcolor = texture(u_source_scene, v_tex_coords);
    color = mix(color, texcolor, texcolor.a);
}