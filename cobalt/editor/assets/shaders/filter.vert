#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex_coords;
layout(location = 2) in vec3 normal;

out vec2 v_tex_coords;

uniform mat4 u_model;

struct CameraStruct {
    mat4 u_view;
    mat4 u_projection;
    vec3 u_cameraPosition;
    int u_targetWidth;
    int u_targetHeight;
    vec3 padding;
};
layout (std140, binding = 0) uniform Camera {  
    CameraStruct u_camera;
};


void main() {
    v_tex_coords = tex_coords;
    gl_Position = u_camera.u_projection * u_camera.u_view * u_model * vec4(position, 1.0);
}