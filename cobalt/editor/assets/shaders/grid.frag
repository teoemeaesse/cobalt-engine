#version 410 core

out vec4 color;

in vec3 v_world_position;
in vec2 v_tex_coords;

uniform sampler2D u_settings;  // alpha: exponent for N, rgb: FADE_RADIUS

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

const int MAX_LIGHTS = 32;
struct LightStruct {
    vec3 u_light_position;
    float u_light_intensity;
    vec3 u_light_color;
    float padding;
};
layout (std140) uniform PointLighting {  
    LightStruct u_lights[MAX_LIGHTS];
    float u_count;
    vec3 padding;
};

const float LINE_WIDTH = 1.0 / 32.0; // This will control the thickness of the lines
const float AA_WIDTH = LINE_WIDTH * 0.5; // Width for anti-aliasing effect

float edgeFactor(vec2 coords, float width) {
    float insideDistance = min(coords.x, min(1.0 - coords.x, min(coords.y, 1.0 - coords.y)));
    return smoothstep(0.0, width, insideDistance);
}

void main() {
    vec4 settings = texture(u_settings, vec2(0.5, 0.5));
    float FADE_RADIUS = settings.r * 16581375.0 + settings.g * 65025 + settings.b * 255.0;
    int N = int(pow(10.0, settings.a * 255.0));
    
    vec3 cameraFront = -normalize(vec3(u_camera.u_view[0][2], u_camera.u_view[1][2], u_camera.u_view[2][2]));
    vec3 toPoint = v_world_position - u_camera.u_cameraPosition;
    float t = dot(toPoint, cameraFront);
    vec3 closestPoint = u_camera.u_cameraPosition + t * cameraFront;
    
    float dist = length(v_world_position - closestPoint);

    float alpha = 1.0 - smoothstep(FADE_RADIUS * 0.3, FADE_RADIUS, dist);
    if (alpha < 0.01) {
        discard;
    }

    vec2 modCoords = mod(v_tex_coords * N + 1, 1.0);
    vec2 gridCoords = v_tex_coords * float(N) + 1;
    
    float aaFactorX = edgeFactor(modCoords, AA_WIDTH);
    float aaFactorY = edgeFactor(modCoords.yx, AA_WIDTH);
    float lineAlpha = min(aaFactorX, aaFactorY);

    bool onXLine = modCoords.x < LINE_WIDTH || 1.0 - modCoords.x < LINE_WIDTH;
    bool onYLine = modCoords.y < LINE_WIDTH || 1.0 - modCoords.y < LINE_WIDTH;
    bool onLine = onXLine || onYLine;
    bool onTenthLine = mod(floor(gridCoords.x - 0.5), 10.0) < LINE_WIDTH && onXLine || mod(floor(gridCoords.y - 0.5), 10.0) < LINE_WIDTH && onYLine;
    bool onTwentiethLine = mod(floor(gridCoords.x - 0.5), 20.0) < LINE_WIDTH && onXLine || mod(floor(gridCoords.y - 0.5), 20.0) < LINE_WIDTH && onYLine;

    alpha = alpha * (1.0 - lineAlpha);
    if (onTwentiethLine) {
        color = vec4(0.8, 0.8, 0.8, alpha); // Thicker or more highlighted for 20th lines
    } else if (onTenthLine) {
        color = vec4(0.4, 0.4, 0.55, alpha); // Slightly highlighted for 10th lines
    } else if (onLine) {
        color = vec4(0.15, 0.15, 0.2, alpha); // Default grid appearance
    } else {
        discard;
    }
}