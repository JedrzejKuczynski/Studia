#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;


//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 normal; //wektor normalny w wierzcholku w przestrzeni modelu
in vec2 texCoord0; //wspolrzedne teksturowania

//Zmienne interpolowane
out vec4 i_l1; //wektor do swiatla(przestrzen oka)
out vec4 i_l2;
out vec4 i_v; //wektor do obserwatora(przestrzen oka)
out vec4 i_n; //wektor normalny (przestrzen oka)
out vec2 iTexCoord0; //wspolrzedne teksturowania

uniform vec4 lp1;
uniform vec4 lp2;


void main(void) {

    //vec4 lp=vec4(0,0,-6,1); //Wspolrzedne swiatla w przestrzeni swiata

    i_l1 = normalize(V*lp1-V*M*vertex);
    i_l2 = normalize(V*lp2-V*M*vertex);
    i_v = normalize(vec4(0,0,0,1)-V*M*vertex);
    i_n = normalize(V*M*normal);

    iTexCoord0 = texCoord0;

	gl_Position = P*V*M*vertex;
}


