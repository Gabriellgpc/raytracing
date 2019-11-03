#ifndef _UTILS_H_
#define _UTILS_H_
#include <glm/glm.hpp>

typedef glm::vec3 Vec;

float randf(float max);                             //gera um numero aleatorio entre 0.0 e max
Vec   randVec(float max);                           //gera um vec3 com floats de 0.0 a max
Vec   randPositionInCube(Vec vertexA, Vec vertexB); //gera uma coordenada dentro de um cubo formado pelos vertices A e B
void  rotate(Vec axis, float ang);

#endif
