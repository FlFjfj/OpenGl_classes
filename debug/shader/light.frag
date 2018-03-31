#version 330 core

uniform sampler2D texture0;

in vec2 v_TexCoord;
in vec3 v_WorldCoord;

out vec4 frag_color;

vec3 light_pos = vec3(0.0, 0.0, 1.0);

void main() {
    light_power = abs(dot(texture2D(texture0, v_TexCoord + veec2(0.5, 0)), v_WorldCoord - light_pos)) * 0.7;
    frag_color = texture2D(texture0, v_TexCoord) * (light_power + 0.3);
}
