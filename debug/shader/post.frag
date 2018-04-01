#version 330 core

uniform sampler2D texture0;

in vec2 v_TexCoord;

out vec4 frag_color;

void main() {
    frag_color = texture2D(texture0, v_TexCoord);
    float gamma = 1 / 1.5;
    frag_color.rgb = pow(frag_color.rgb, vec3(1.0/gamma));
}
