#version 330 core

uniform sampler2D texture0;

in vec2 v_TexCoord;
in vec3 v_WorldCoord;

out vec4 frag_color;

vec3 light_pos = vec3(0.0, 0.0, -100.0);

void main() {
    float light_power = abs(
                            dot(
                                normalize(2 * texture2D(texture0, vec2(v_TexCoord.x + 0.5, v_TexCoord.y)).xyz - vec3(1.0)),
                                normalize(light_pos - v_WorldCoord)
                                )
                            ) * 0.7;
    frag_color = texture2D(texture0, v_TexCoord) * (0.3 + light_power);

}
