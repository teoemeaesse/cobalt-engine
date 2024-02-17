#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex_coords;

out vec2 v_tex_coords;

struct CameraStruct {
    mat4 u_view;
    mat4 u_projection;
    int u_targetWidth;
    int u_targetHeight;
    vec2 padding;
};
layout (std140) uniform Camera {  
    CameraStruct u_camera;
};

void main() {
    v_tex_coords = tex_coords;
    gl_Position = u_camera.u_projection * u_camera.u_view * vec4(position, 1.0);
}