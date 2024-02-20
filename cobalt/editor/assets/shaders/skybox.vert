#version 410 core

layout(location = 0) in vec3 position;

out vec3 v_tex_coords;

struct CameraStruct {
    mat4 u_view;
    mat4 u_projection;
    vec3 u_cameraPosition;
    int u_targetWidth;
    int u_targetHeight;
    vec3 padding;
};
layout (std140) uniform Camera {  
    CameraStruct u_camera;
};

void main() {
    v_tex_coords = position;
    mat4 view = u_camera.u_view;
    view[3][0] = 0.0;
    view[3][1] = 0.0;
    view[3][2] = 0.0;
    gl_Position = (u_camera.u_projection * view * vec4(position, 1.0)).xyww;
}