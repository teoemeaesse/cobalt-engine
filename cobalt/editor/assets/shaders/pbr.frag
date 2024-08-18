#version 410 core

out vec4 color;

uniform sampler2D u_albedo;
uniform sampler2D u_normal;
uniform sampler2D u_mrao;

in vec3 v_world_position;
in vec2 v_tex_coords;
in vec3 v_normal;

const float PI = 3.14159265359;

const int MAX_LIGHTS = 32;

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

struct LightStruct {
    vec3 u_lightPosition;
    float u_lightIntensity;
    vec3 u_lightColor;
    float padding;
};
layout (std140) uniform PointLighting {  
    LightStruct u_lights[MAX_LIGHTS];
    float u_lightCount;
    vec3 padding;
};

/** 
 * @brief Get normal from normal map.
 * https://learnopengl.com/#!PBR/Lighting
 */
vec3 getNormalFromMap() {
    vec3 tangentNormal = texture(u_normal, v_tex_coords).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(v_world_position);
    vec3 Q2  = dFdy(v_world_position);
    vec2 st1 = dFdx(v_tex_coords);
    vec2 st2 = dFdy(v_tex_coords);

    vec3 N   = normalize(v_normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

/** 
 * @brief Trowbridge-Reitz GGX Normal Distribution Function.
 * https://learnopengl.com/#!PBR/Lighting
 * @param n normal.
 * @param h half vector.
 * @param a roughness.
 */
float normalDist(vec3 n, vec3 h, float a) {
    float a2     = a * a;
    float ndh    = max(dot(n, h), 0.0);
    float ndh2   = ndh * ndh;
    float nom    = a2;
    float denom  = ndh2 * (a2 - 1.0) + 1.0;
    denom        = PI * denom * denom;
    return nom / denom;
}

/** 
 * @brief Smith's method using the Schlick-Beckmann.
 * approximation of the Geometric Shadowing Function.
 * https://learnopengl.com/#!PBR/Lighting
 * @param n normal.
 * @param v view vector.
 * @param l light vector.
 * @param a roughness.
 */
float geometrySchlickGGX(float NdotV, float a) {
    float r = (a + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
float geometrySmith(vec3 N, vec3 V, vec3 L, float a) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = geometrySchlickGGX(NdotV, a);
    float ggx1 = geometrySchlickGGX(NdotL, a);

    return ggx1 * ggx2;
}

/** 
 * @brief Fresnel-Schlick approximation.
 * https://learnopengl.com/#!PBR/Lighting
 * @param cosTheta cosine of the angle between the normal and the view vector.
 * @param f0 base reflectivity.
 */
vec3 fresnelSchlick(float cosTheta, vec3 f0) {
    return f0 + (1.0 - f0) * pow(1.0 - cosTheta, 5.0);
}

void main() {
    vec3 albedo     = pow(texture(u_albedo, v_tex_coords).rgb, vec3(2.2));
    vec3 normal     = texture(u_normal, v_tex_coords).rgb;
    vec3 mrao       = texture(u_mrao, v_tex_coords).rgb;
    float metallic  = mrao.r;
    float roughness = mrao.g;
    float ao        = mrao.b;

    vec3 n = getNormalFromMap();
    vec3 v = normalize(u_camera.u_cameraPosition - v_world_position);

    vec3 f0 = vec3(0.04);
    f0 = mix(f0, albedo, metallic);

    // reflectance equation
    vec3 lo = vec3(0.0);
    int lightCount = min(int(u_lightCount) + 1, MAX_LIGHTS);
    for(int j = 0; j < lightCount; j++) {
        for(int i = 0; i < 2; i++) {
            vec3 lightPosition = u_lights[j].u_lightPosition;

            // calculate per-light radiance
            vec3 l = normalize(lightPosition - v_world_position);
            vec3 h = normalize(v + l);
            float distance    = length(lightPosition - v_world_position);
            float attenuation = 1.0 / (distance * distance);
            vec3 radiance     = u_lights[j].u_lightColor * attenuation * 10000;
            
            // cook-torrance brdf
            float ndf = normalDist(n, h, roughness);
            float g   = geometrySmith(n, v, l, roughness);
            vec3 f    = fresnelSchlick(max(dot(h, v), 0.0), f0);
            
            vec3 ks = f;
            vec3 kd = vec3(1.0) - ks;
            kd *= 1.0 - metallic;
            
            vec3 specular = ndf * g * f / (4.0 * max(dot(n, v), 0.0) * max(dot(n, l), 0.0) + 0.0001);

            // add to outgoing radiance lo
            float ndl = max(dot(n, l), 0.0);
            lo += (kd * albedo / PI + specular) * radiance * ndl;
        }
    }
  
    vec3 ambient = vec3(0.1) * albedo * ao;
    color = vec4(ambient + lo, 1.0);
}