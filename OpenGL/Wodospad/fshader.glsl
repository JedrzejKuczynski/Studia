#version 330

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 i_l1; //wektor do swiatla(przestrzen oka)
in vec4 i_l2;
in vec4 i_v; //wektor do obserwatora(przestrzen oka)
in vec4 i_n; //wektor normalny (przestrzen oka)
in vec2 iTexCoord0; //wspolrzedne teksturowania

uniform sampler2D textureMap0;

void main(void) {
	vec4 v = normalize(i_v);
    vec4 n = normalize(i_n);
    vec4 l1 = normalize(i_l1);
    vec4 l2 = normalize(i_l2);
    vec4 r1 = reflect(-l1,n);
    vec4 r2 = reflect(-l2,n);


    vec4 ka = vec4(0,0,0,0); //Kolor obiektu w swietle otoczenia
    vec4 kd = texture(textureMap0,iTexCoord0); //Kolor obiektu w swietle rozproszonym
    vec4 ks = vec4(0.007937, 0.007937, 0.007937, 0); //Kolor obiektu w swietle odbitym

    vec4 la = vec4(0,0,0,0); //Kolor swiatla otoczenia
    vec4 ld = vec4(1,1,1,1); //Kolor swiatla rozpraszanego
    vec4 ls = vec4(1,1,1,0); //Kolor swiatla odbijanego

    float nl_1 = max(dot(n,l1),0); //Kosinus kata pomiedzy wektorami do swiatla i normalnym
    float nl_2 = max(dot(n,l2),0);
    float rv1 = pow(max(dot(r1,v),0),14); //Kosinus kata pomiedzy wektorami do obserwatora i odbitym, podniesiony do wykladnika Phonga
    float rv2 = pow(max(dot(r2,v),0),14);

	pixelColor = ka*la+kd*ld*vec4(nl_1,nl_1,nl_1,1)+ks*ls*vec4(rv1,rv1,rv1,0);
	pixelColor += ka*la+kd*ld*vec4(nl_2,nl_2,nl_2,1)+ks*ls*vec4(rv2,rv2,rv2,0);
}
