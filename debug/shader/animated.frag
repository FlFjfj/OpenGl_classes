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

void main() {
    float light_power = abs(
                            dot(
                                normalize(2 * texture2D(texture0, vec2(v_TexCoord.x + 0.5, v_TexCoord.y + v_Frame / float(u_FrameCount))).xyz - vec3(1.0)),
                                normalize(light_pos - v_WorldCoord)
                                )
                            ) * 0.5;
    frag_color = mix(texture2D(texture0, vec2(v_TexCoord.x, v_TexCoord.y + v_Frame / float(u_FrameCount))),
                     texture2D(texture0, vec2(v_TexCoord.x, v_TexCoord.y + (v_Frame + 1) % u_FrameCount / float(u_FrameCount))),
                     v_Trans) * (0.5 + light_power);
}
