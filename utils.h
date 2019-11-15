#ifndef _UTILS_H_
#define _UTILS_H_
#include <glm/glm.hpp>

typedef glm::vec3 Vec;

float randf();                             //gera um numero aleatorio entre 0.0 e 1.0
Vec   randVec();                           //gera um vec3 com floats de 0.0 a 1.0
Vec   randPositionInCube(Vec center, int edge); //gera uma coordenada dentro de um cubo de aresta edge e com centro em pos

class Ray{
public:
  Vec orig;
  Vec dir;

  Ray():orig(0,0,0), dir(0,0,0){}
  Ray(Vec orig, Vec dir):orig(orig), dir(dir){}
};

#endif
