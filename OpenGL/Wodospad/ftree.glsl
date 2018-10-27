#version 330

out vec4 pixelColor;

in vec2 iTexCoord2; //wspolrzedne teksturowania

uniform sampler2D textureMap2;

void main(void){

    vec4 leaf = texture(textureMap2, iTexCoord2);

    pixelColor = leaf;
}

