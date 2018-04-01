#version 330 core
#define M_PI 3.1415926535897932384626433832795

uniform sampler2D texture0;
uniform float u_Time;

in vec2 v_TexCoord;

out vec4 frag_color;

float v1 = 2.0;
float w1 = u_Time / 2;

void main() {
    float x = v_TexCoord.x;
    float c1 = -sin(2*(x * v1 + w1)) + 2 * x * v1 + sin(2 * w1);
    float c2 = -sin(2 * (v1 + w1)) + 2 * v1 + sin(2*w1);

    vec4 buf_color = texture2D(texture0, vec2(c1 / c2, v_TexCoord.y));
    frag_color = mix(buf_color, texture2D(texture0, v_TexCoord), 0.94);
}
