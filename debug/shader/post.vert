#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

out vec2 v_TexCoord;
out vec2 v_Position;

uniform mat4 u_ModelTrans;
uniform float u_Time;

void main() {
  v_TexCoord = vec2(a_TexCoord.x, 1 - a_TexCoord.y);
  vec4 pos = u_ModelTrans * vec4(a_Position + vec3(sin(u_Time), cos(2 * u_Time),0) / 200, 1.0);
  v_Position = pos.xy;
  gl_Position = pos;
}
