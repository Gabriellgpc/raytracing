#include <stdio.h>
#include "object.h"

int main(){
  printf("Programa Teste de Object\n");
  Object *plane = new Plane(Material(), Vec(0.0, 0.0, 1.0), Vec(1.0, 1.0, 1.0));
  Vec orig(0.0, 0.0, 0.0), dir(1.0, -1.0, 0.0);

  Vec point;
  double distance;
  if(plane->intersectRay(orig, dir, point, distance))
  {
    printf("Plano: Pointo de intersecao: (%f, %f, %f)\nDistancia:%f\n",
          point.x, point.y, point.z, distance);
  }else{
    printf("Plano: Nao ha intersecao\n");
  }

  Object *sphere = new Sphere(Material(), Vec(1.0, 1.0, 1.0), 0.5);
  orig = Vec(0.0, 0.0, 0.0);
  dir  = Vec(0.0, 0.0, 1.0);

  if(sphere->intersectRay(orig, dir, point, distance))
  {
    printf("sphere: Pointo de intersecao: (%f, %f, %f)\nDistancia:%f\n",
          point.x, point.y, point.z, distance);
  }else{
    printf("sphere: Nao ha intersecao\n");
  }

  return 0;
}
