#version 330

// CIEMNOŒÆ I SKACZ¥CE ŒWIAT£A // WEKTOR NORMALNY? PUNKTY? ORAZ WYKŁADNIK PHONGA

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

uniform vec4 normal;
uniform vec4 lp1;
uniform vec4 lp2;

in vec4 vertex;

out vec4 i_l1; //wektor do swiatla(przestrzen oka)
out vec4 i_l2;
out vec4 i_v; //wektor do obserwatora(przestrzen oka)
out vec4 i_n; //wektor normalny (przestrzen oka)
out vec2 iTexCoord1;

void main(void) {

    i_l1 = normalize(V*lp1-V*M*vertex);
    i_l2 = normalize(V*lp2-V*M*vertex);
    i_v = normalize(vec4(0,0,0,1)-V*M*vertex);
    i_n = normalize(V*M*normal);

    iTexCoord1 = vertex.xz;

    gl_Position = P * V * M * vertex;
}
