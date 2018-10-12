#version 330 core

uniform sampler2D texture0;

in vec2 v_TexCoord;
in vec2 v_Position;

out vec4 frag_color;

void main() {
    vec4 texColor = texture2D(texture0, v_TexCoord);
    vec4 movedColor = vec4(texture2D(texture0, v_TexCoord - (v_Position * 0.000)).r,
                           texture2D(texture0, v_TexCoord - (v_Position * 0.007)).g,
                           texture2D(texture0, v_TexCoord - (v_Position * 0.014)).b,
                           1.0
                           );

    frag_color = mix(texColor, movedColor, 0.85);

    vec2 pos = v_Position * vec2(256, 144);
    float dx = abs(pos.x - floor(pos.x));
    float dy = abs(pos.y - floor(pos.y));

    if(dx < 0.05 || dx > 0.95 || dy < 0.05 || dy > 0.95) {
      frag_color.xyz *= 0.95;
    }

    float gamma = 1 / 1.5;
    frag_color.rgb = pow(frag_color.rgb, vec3(1.0/gamma));
}
