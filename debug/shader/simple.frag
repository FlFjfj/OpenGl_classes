#version 330 core

uniform sampler2D texture0;
uniform mat4 u_ModelTrans;
uniform mat4 u_ProjTrans;


in vec2 v_TexCoord;

out vec4 frag_color;

void main() {
    frag_color = texture2D(texture0, v_TexCoord);
}
