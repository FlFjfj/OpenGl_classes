#version 410 core

uniform mat4 u_ModelTrans;
uniform mat4 u_ProjTrans;

uniform int u_FrameCount;
uniform float u_FrameTime;
uniform float u_Time;

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoord;
out vec3 v_WorldCoord;
flat out int v_Frame;
flat out float v_Trans;

float norm(float x) {
    return x - trunc(x);
}

void main() {
    v_Frame = int(trunc(u_Time / u_FrameTime)) % u_FrameCount;
    v_Trans = norm(u_Time / u_FrameTime);

    v_TexCoord = vec2(a_TexCoord.x / 2, a_TexCoord.y / u_FrameCount);
    vec4 vert = u_ModelTrans * vec4(a_Position, 1.0);
    v_WorldCoord = vert.xyz;
	gl_Position = u_ProjTrans * vert;
}
