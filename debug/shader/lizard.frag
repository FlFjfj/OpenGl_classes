#version 410 core

uniform sampler2D texture0;

uniform int u_FrameCount;
uniform float u_FrameTime;
uniform float u_Time;

in vec2 v_TexCoord;
in vec3 v_WorldCoord;
flat in int v_Frame;
flat in float v_Trans;

out vec4 frag_color;


vec3 light_pos = vec3(0.0, 0.0, -100.0);

float norm(float x) {
    return x - trunc(x);
}

vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec4 rotateHue(vec4 c) {
    vec4 bright_color = c;
    vec3 hsv_color = rgb2hsv(bright_color.rgb);
    hsv_color.r = (hsv_color.r + u_Time / 4.) - floor(hsv_color.r + u_Time / 4.);
    bright_color.rgb = hsv2rgb(hsv_color);
    return bright_color;
}

void main() {
    float light_power = abs(
                            dot(
                                normalize(2 * texture2D(texture0, vec2(v_TexCoord.x + 0.5, v_TexCoord.y + v_Frame / float(u_FrameCount))).xyz - vec3(1.0)),
                                normalize(light_pos - v_WorldCoord)
                                )
                            ) * 0.3;
    vec4 color1 = texture2D(texture0, vec2(v_TexCoord.x, v_TexCoord.y + v_Frame / float(u_FrameCount)));
    vec4 color2 = texture2D(texture0, vec2(v_TexCoord.x, v_TexCoord.y + (v_Frame + 1) % u_FrameCount / float(u_FrameCount)));
    vec4 color = rotateHue(mix(color1, color2, 0));

    frag_color = vec4((color * (0.7 + light_power)).xyz, color.a);
}
