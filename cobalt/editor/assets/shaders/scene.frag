#version 430 core

out vec4 color;

uniform int u_targetWidth;
uniform int u_targetHeight;


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
    float ggx2 = ndl / (ndl * (1.0 - k) + k)
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
    color = vec4(1.0, 0.0, 0.5, 1.0);
}