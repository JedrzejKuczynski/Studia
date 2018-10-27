#version 330

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

in vec4 vertex;
out vec2 iTexCoord2;

void main(void) {

    iTexCoord2 = vertex.xz;
    gl_Position = P * V * M * vertex;
}
