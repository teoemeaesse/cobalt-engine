#version 430 core

out vec4 color;

uniform int u_targetWidth;
uniform int u_targetHeight;

uniform sampler2D u_albedo;
uniform sampler2D u_normal;
uniform sampler2D u_mrao;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 camPos;

in vec3 v_world_position;
in vec2 v_tex_coords;
in vec3 v_normal;

const float PI = 3.14159265359;

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

/* Trowbridge-Reitz GGX Normal Distribution Function.
 * https://learnopengl.com/#!PBR/Lighting
 * @param n: normal.
 * @param h: half vector.
 * @param a: roughness.
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

/* Smith's method using the Schlick-Beckmann.
 * approximation of the Geometric Shadowing Function.
 * https://learnopengl.com/#!PBR/Lighting
 * @param n: normal.
 * @param v: view vector.
 * @param l: light vector.
 * @param k: remapping of the roughness.
 */
float geometrySmith(vec3 n, vec3 v, vec3 l, float k) {
    float ndv = max(dot(n, v), 0.0);
    float ndl = max(dot(n, l), 0.0);
    float ggx1 = ndv / (ndv * (1.0 - k) + k);
    float ggx2 = ndl / (ndl * (1.0 - k) + k);
    return ggx1 * ggx2;
}

/* Fresnel-Schlick approximation.
 * https://learnopengl.com/#!PBR/Lighting
 * @param cosTheta: cosine of the angle between the normal and the view vector.
 * @param f0: base reflectivity.
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

    vec3 n = normalize(normal);
    vec3 v = normalize(camPos - v_world_position);

    vec3 f0 = vec3(0.04);
    f0 = mix(f0, albedo, metallic);

    // reflectance equation
    vec3 lo = vec3(0.0);
    for(int i = 0; i < 1; i++) {
        // calculate per-light radiance
        vec3 l = normalize(lightPosition - v_world_position);
        vec3 h = normalize(v + l);
        float distance    = length(lightPosition - v_world_position);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance     = lightColor * attenuation;
        
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
  
    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 c = ambient + lo;

    c = c / (c + vec3(1.0));
    c = pow(c, vec3(1.0/2.2));

    color = vec4(c, 1.0);
}