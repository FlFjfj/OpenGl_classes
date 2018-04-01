#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoord;

uniform mat4 u_ModelTrans;
uniform mat4 u_ProjTrans;
uniform int u_Size;
uniform int u_Data;

void main() {
    v_TexCoord = vec2(a_TexCoord.x / u_Size + u_Data / float(u_Size) , a_TexCoord.y);
	gl_Position = u_ProjTrans * u_ModelTrans * vec4(a_Position, 1.0);
}
