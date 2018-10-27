#ifndef ROCK_H
#define ROCK_H

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ios>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;
using namespace glm;

class Rock{

public:

    float* vertices;
    float* uvs;
    float* normals;
    int vertexCount;

    Rock(string path){
        loadOBJ(path);
    }

    ~Rock(){}

    void loadOBJ(string path){

        vector <float> faceVertices, faceUVs, faceNormals;
        vector <float> tmpVertices, tmpUVs, tmpNormals;

        ifstream file(path.c_str(), ios::in);
        string line;

        while(getline(file, line)){

            if(line.substr(0, 2) == "v "){

                istringstream sub(line.substr(2));
                float x, y, z, w;
                sub >> x;
                sub >> y;
                sub >> z;
                w = 1.0f;
                tmpVertices.push_back(x);
                tmpVertices.push_back(y);
                tmpVertices.push_back(z);
                tmpVertices.push_back(w);

            } else if(line.substr(0,3) == "vt "){

                istringstream sub(line.substr(3));
                float u, v;
                sub >> u;
                sub >> v;
                tmpUVs.push_back(u);
                tmpUVs.push_back(v);
            } else if(line.substr(0,3) == "vn "){

                istringstream sub(line.substr(3));
                float x, y, z, w;
                sub >> x;
                sub >> y;
                sub >> z;
                w = 0.0f;
                tmpNormals.push_back(x);
                tmpNormals.push_back(y);
                tmpNormals.push_back(z);
                tmpNormals.push_back(w);

            } else if(line.substr(0, 2) == "f "){

                string sub = line.substr(2);
                char* dup = strdup(sub.c_str());
                char* token = strtok(dup, " ");
                while(token != NULL){
                    istringstream info(token);
                    vector <int> tokens;
                    string data;
                    int index;
                    while(getline(info, data, '/')){
                        index = atoi(data.c_str());
                        index--;
                        tokens.push_back(index);
                    }
                    faceVertices.push_back(tokens[0]);
                    faceUVs.push_back(tokens[1]);
                    faceNormals.push_back(tokens[2]);
                    tokens.clear();
                    token = strtok(NULL, " ");
                }
            }
        }

        vertices = new float[faceVertices.size()*4];
        uvs = new float[faceUVs.size()*2];
        normals = new float[faceNormals.size()*4];
        vertexCount = faceVertices.size();

        int index_out = 0;

        for(int i = 0; i < faceVertices.size(); i++){
            int vIndex = faceVertices[i]*4;
            vertices[index_out] = tmpVertices[vIndex];
            index_out++;
            vIndex++;
            vertices[index_out] = tmpVertices[vIndex];
            index_out++;
            vIndex++;
            vertices[index_out] = tmpVertices[vIndex];
            index_out++;
            vIndex++;
            vertices[index_out] = tmpVertices[vIndex];
            index_out++;
            vIndex++;
        }

        index_out = 0;

        for(int i = 0; i < faceUVs.size(); i++){
            int uvIndex = faceUVs[i]*2;
            uvs[index_out] = tmpUVs[uvIndex];
            index_out++;
            uvIndex++;
            uvs[index_out] = tmpUVs[uvIndex];
            index_out++;
            uvIndex++;
        }

        index_out = 0;

        for(int i = 0; i < faceNormals.size(); i++){
            int nIndex = faceNormals[i]*4;
            normals[index_out] = tmpNormals[nIndex];
            index_out++;
            nIndex++;
            normals[index_out] = tmpNormals[nIndex];
            index_out++;
            nIndex++;
            normals[index_out] = tmpNormals[nIndex];
            index_out++;
            nIndex++;
            normals[index_out] = tmpNormals[nIndex];
            index_out++;
            nIndex++;
        }
    }
};

#endif
