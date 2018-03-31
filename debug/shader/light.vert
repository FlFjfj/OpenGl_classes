#version 330 core

uniform mat4 u_ModelTrans;
uniform mat4 u_ProjTrans;

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoord;
out vec3 v_WorldCoord;

void main() {
    v_TexCoord = vec2(a_TexCoord.x / 2, a_TexCoord.y);
    vec4 vert = u_ModelTrans * vec4(a_Position, 1.0);
    v_WorldCoord = vert.xyz;
	gl_Position = u_ProjTrans * vert;
}
