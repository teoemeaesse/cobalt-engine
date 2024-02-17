#version 410 core

out vec4 color;

in vec2 v_tex_coords;

uniform vec4 u_grid_color;

void main() {
    float ddx = dFdx(v_tex_coords);
    float ddy = dFdy(v_tex_coords);

    vec2 w = max(abs(ddx), abs(ddy)) + 0.01;

    vec2 a = p + 0.5*w;
    vec2 b = p - 0.5*w;
    vec2 i = (floor(a)+min(fract(a)*N,1.0)-floor(b)-min(fract(b)*N,1.0))/(N*w);

    color = vec4(1.0, 0.0, 0.0, (1.0-i.x)*(1.0-i.y));
}