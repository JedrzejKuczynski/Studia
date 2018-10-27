/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "rock.h"

using namespace glm;

struct WaterParticle{
    vec3 velocity;
    vec3 position;
    float life;

    WaterParticle(bool initialize){
        position = vec3(0, 0, 0);
        velocity = vec3(0, 0, 0);
        life = -5;
    }

    WaterParticle(){
        float offset_positionx = -0.3 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.3+0.3)));
        float offset_positionz = 0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.4)));
        //float offset_velocity = -0.5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0+0.5)));
        position = vec3(0, 0.3, 0.5) + vec3(offset_positionx, 0, offset_positionz);
        velocity = vec3(0, 0.2, -0.5); // + vec3(0, 0, offset_velocity);
        life = 2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(8-2)));
    }
};

const int coneVertexCount=11;
const int treesCount = 12;

struct Tree{
    float treeVertices[coneVertexCount*4];

    Tree(float x, float z, float y)
    {
        treeVertices[0]= x; treeVertices[1]=y; treeVertices[2]=z; treeVertices[3]=1;
        int i = 4;

        for (int angle = 0; angle <= 360; angle+=40) {
            treeVertices[i]=x+(sin(angle* 3.14/180) *0.25);//sin(kąt*pi/180)*radius);
            treeVertices[i+1]=0;
            treeVertices[i+2]=z+(cos(angle* 3.14/180) *0.25);
            treeVertices[i+3]=1;
            i+=4;
        }
    }
    Tree(){}
};

void initializeSystem(WaterParticle *waterfall, int particlesNumber){
    for(int i = 0; i < particlesNumber; i++)
        waterfall[i] = WaterParticle(true);
}

float speed_x = 0; // [radiany/s]
float speed_y = 0; // [radiany/s]

Rock rock = Rock("avatar_mountain.obj");
float* vertices = rock.vertices;
float* texCoords = rock.uvs;
float* normals = rock.normals;
int vertexCount = rock.vertexCount;

const int MaxParticles = 100000;
vec3 gravity = vec3(0, -1, 0);
WaterParticle waterfall[MaxParticles];
float aliveParticles[MaxParticles*4];

Tree trees[treesCount];
float allTreesVertices[treesCount*coneVertexCount*4];

float aspect = 1; //Stosunek szerokości do wysokości okna

//Uchwyty na shadery
ShaderProgram *shaderProgram; //Wskaźnik na obiekt reprezentujący program cieniujący.
ShaderProgram *particleShader;
ShaderProgram *treeShader;

GLuint tex;
GLuint tex2;
GLuint tex3;

//Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

//Procedura obsługi klawiatury
void key_callback(GLFWwindow* window, int key,
	int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) speed_y = -3.14;
		if (key == GLFW_KEY_RIGHT) speed_y = 3.14;
		if (key == GLFW_KEY_UP) speed_x = -3.14;
		if (key == GLFW_KEY_DOWN) speed_x = 3.14;
	}


	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT) speed_y = 0;
		if (key == GLFW_KEY_RIGHT) speed_y = 0;
		if (key == GLFW_KEY_UP) speed_x = 0;
		if (key == GLFW_KEY_DOWN) speed_x = 0;
	}
}

//Procedura obługi zmiany rozmiaru bufora ramki
void windowResize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); //Obraz ma być generowany w oknie o tej rozdzielczości
    if (height != 0) {
        aspect = (float)width/(float)height; //Stosunek szerokości do wysokości okna
    } else {
        aspect = 1;
    }
}


GLuint readTexture(char* filename) {
  GLuint tex;
  glActiveTexture(GL_TEXTURE0);

  //Wczytanie do pamięci komputera
  std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
  unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
  //Wczytaj obrazek
  unsigned error = lodepng::decode(image, width, height, filename);

  //Import do pamięci karty graficznej
  glGenTextures(1,&tex); //Zainicjuj jeden uchwyt
  glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
  //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
  glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
    GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  return tex;
}

//Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	glClearColor(0, 0, 0, 1); //Czyść ekran na czarno
	glEnable(GL_DEPTH_TEST); //Włącz używanie Z-Bufora
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glfwSetKeyCallback(window, key_callback); //Zarejestruj procedurę obsługi klawiatury
	glfwSetFramebufferSizeCallback(window,windowResize); //Zarejestruj procedurę obsługi zmiany rozmiaru bufora ramki

	shaderProgram = new ShaderProgram("vshader.glsl",NULL,"fshader.glsl"); //Wczytaj program cieniujący
	particleShader = new ShaderProgram("vparticle.glsl", NULL, "fparticle.glsl");
	treeShader = new ShaderProgram("vtree.glsl", NULL, "ftree.glsl");

    initializeSystem(waterfall, MaxParticles);

	tex = readTexture("avatar_mountain.png");
	tex2 = readTexture("water.png");
	tex3 = readTexture("tree.png");
}

//Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram() {
	delete shaderProgram; //Usunięcie programu cieniującego
	delete particleShader;
	delete treeShader;

	glDeleteTextures(1,&tex);
	glDeleteTextures(1,&tex2);
	glDeleteTextures(1,&tex3);
}

void drawObject(ShaderProgram *shaderProgram, mat4 mP, mat4 mV, mat4 mM) {

	shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->getUniformLocation("P"),1, false, value_ptr(mP));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("V"),1, false, value_ptr(mV));
	glUniformMatrix4fv(shaderProgram->getUniformLocation("M"),1, false, value_ptr(mM));

    glUniform4f(shaderProgram->getUniformLocation("lp1"), 0, 0, -6, 1);
    glUniform4f(shaderProgram->getUniformLocation("lp2"), 0, 10, 0, 1);
	glUniform1i(shaderProgram->getUniformLocation("textureMap0"), 0);

	//Przypisz tekstury do jednostek teksturujących
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,tex);

    glEnableVertexAttribArray(shaderProgram->getAttribLocation("vertex"));
    glEnableVertexAttribArray(shaderProgram->getAttribLocation("normal"));
    glEnableVertexAttribArray(shaderProgram->getAttribLocation("texCoord0"));

    glVertexAttribPointer(shaderProgram->getAttribLocation("vertex"),4,GL_FLOAT,false,0,vertices);
    glVertexAttribPointer(shaderProgram->getAttribLocation("normal"),4,GL_FLOAT,false,0,normals);
    glVertexAttribPointer(shaderProgram->getAttribLocation("texCoord0"),2,GL_FLOAT,false,0,texCoords);

    glVertexAttribDivisor(shaderProgram->getAttribLocation("vertex"), 0); // Czemu tak to ja nie wiem.

    glDrawArrays(GL_TRIANGLES,0,vertexCount);

	glDisableVertexAttribArray(shaderProgram->getAttribLocation("vertex"));
    glDisableVertexAttribArray(shaderProgram->getAttribLocation("normal"));
    glDisableVertexAttribArray(shaderProgram->getAttribLocation("texCoord0"));
}

void processWaterfall(ShaderProgram *shader, mat4 mM, mat4 mV, mat4 mP, double timestep) {

    shader->use();

    glUniformMatrix4fv(shader->getUniformLocation("P"),1, false, value_ptr(mP));
	glUniformMatrix4fv(shader->getUniformLocation("V"),1, false, value_ptr(mV));
	glUniformMatrix4fv(shader->getUniformLocation("M"),1, false, value_ptr(mM));

	glUniform1i(shader->getUniformLocation("textureMap1"), 0);
	glUniform4f(shader->getUniformLocation("lp1"), 0, 0, -6, 1);
    glUniform4f(shader->getUniformLocation("lp2"), 0, 10, 0, 1);
	glUniform4f(shader->getUniformLocation("normal"), 0, 1, 0, 0);

    int particle_count = 0;
	int index = 0;

    for(int i = 0; i < MaxParticles; i++){
        WaterParticle &p = waterfall[i];
        p.life -= timestep;
        if(p.life > 0.0f){
            if(p.position.z < -0.35){
                float offset_velocity = -0.5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0+0.5)));
                p.velocity += (gravity + vec3(0, offset_velocity, 0)) * float(timestep);
            }
            p.position += p.velocity * (float)timestep;
            aliveParticles[index] = p.position.x;
            aliveParticles[index+1] = p.position.y;
            aliveParticles[index+2] = p.position.z;
            aliveParticles[index+3] = 1.0f;
            index += 4;
            particle_count++;
        }else{
            waterfall[i] = WaterParticle();
            waterfall[i].life -= 2 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(4-2)));
        }
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,tex2);

	glEnableVertexAttribArray(shader->getAttribLocation("vertex"));

	glVertexAttribPointer(shader->getAttribLocation("vertex"), 4, GL_FLOAT, false, 0, aliveParticles);

    glPointSize(2.0f);

    glVertexAttribDivisor(shader->getAttribLocation("vertex"), 1);

    glDrawArraysInstanced(GL_POINTS, 0, 4, particle_count);

	glDisableVertexAttribArray(shader->getAttribLocation("vertex"));
}


void drawTree(ShaderProgram *shadertree, mat4 mP, mat4 mV, mat4 mM, Tree *tree) {
    float z1 = -0.2; float height = 1;
    float z2 = -0.25; float height2 = 1.075;

    for(int i = 0; i < treesCount; i++)
    {
        if (i <= 6) {
                if(i % 2 == 0) tree[i] = Tree(-0.40,z1,height);
                else tree[i] = Tree(-0.6,z1,height);
                z1 += 0.11; height -= 0.06; }
        else  { if(i % 2 == 0) tree[i] = Tree(0.40,z2,height2);
                else tree[i] = Tree(0.50,z2,height2);
                z2 += 0.15; height2 -= 0.025; }
    }

    int index = 0;
    for(int i = 0; i < treesCount; i++)
    {
        int index2 =0;
        for(int j = 0; j < coneVertexCount; j++){
            allTreesVertices[index] = tree[i].treeVertices[index2];
            allTreesVertices[index+1] = tree[i].treeVertices[index2+1];
            allTreesVertices[index+2] = tree[i].treeVertices[index2+2];
            allTreesVertices[index+3] = 1.0f;
            index += 4;
            index2 += 4;}
    }

	shadertree->use();

	glUniformMatrix4fv(shadertree->getUniformLocation("P"),1, false, value_ptr(mP));
	glUniformMatrix4fv(shadertree->getUniformLocation("V"),1, false, value_ptr(mV));
	glUniformMatrix4fv(shadertree->getUniformLocation("M"),1, false, value_ptr(mM));

    glUniform1i(shadertree->getUniformLocation("textureMap2"), 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,tex3);

    glEnableVertexAttribArray(shadertree->getAttribLocation("vertex"));

    glVertexAttribPointer(shadertree->getAttribLocation("vertex"),4,GL_FLOAT,false,0,allTreesVertices);
    int p = 0;
    for (int i =0; i < treesCount; i++){
        glDrawArrays(GL_TRIANGLE_FAN, p, coneVertexCount); p += coneVertexCount;}

	glDisableVertexAttribArray(shadertree->getAttribLocation("vertex"));
}


//Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle_x, float angle_y, double timestep) {

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Wykonaj czyszczenie bufora kolorów i głębokości

	mat4 P = glm::perspective(60 * PI / 180, aspect, 1.0f, 50.0f); //Wylicz macierz rzutowania

	mat4 V = lookAt( //Wylicz macierz widoku
		vec3(0.0f, 0.0f, -5.0f),
		vec3(0.0f, 0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f));


	//Wylicz macierz modelu rysowanego obiektu
	mat4 M = glm::mat4(1.0f);
	//M = rotate(M, -30*PI/180, vec3(0, 0, 1));
	M = rotate(M, angle_x, vec3(1, 0, 0));
	M = rotate(M, angle_y, vec3(0, 1, 0));

    //Narysuj obiekt
	drawObject(shaderProgram,P,V,M);
	drawTree(treeShader,P,V,M,trees);
	processWaterfall(particleShader, M, V, P, timestep);

	//Przerzuć tylny bufor na przedni
	glfwSwapBuffers(window);

}



int main(void)
{
    srand(time(NULL));
	GLFWwindow* window; //Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) { //Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjujące

	float angle_x = 0; //Kąt obrotu obiektu
	float angle_y = 0; //Kąt obrotu obiektu

	glfwSetTime(0); //Wyzeruj licznik czasu

	//Główna pętla
	while (!glfwWindowShouldClose(window)) //Tak długo jak okno nie powinno zostać zamknięte
	{
		angle_x += speed_x*glfwGetTime(); //Zwiększ kąt o prędkość kątową razy czas jaki upłynął od poprzedniej klatki
		angle_y += speed_y*glfwGetTime();//Zwiększ kąt o prędkość kątową razy czas jaki upłynął od poprzedniej klatki
		double timestep = glfwGetTime();
        glfwSetTime(0);
		drawScene(window,angle_x,angle_y, timestep); //Wykonaj procedurę rysującą
		glfwPollEvents(); //Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram();

	glfwDestroyWindow(window); //Usuń kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
