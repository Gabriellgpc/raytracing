#include "object.h"

#include <cmath>


Material::Material()
{
  this->ks = randf();
  this->kd = 1.0 - randf();
  this->n_shiny = 2.0*randf() + 1.0;
  this->color = randVec();
}

Material::Material(const Material &material)
{
  *this = material;
}
bool Sphere::intersectRay(const Vec &orig, const Vec &dir, Vec &point, double &distance)
{
  float a, b, c;
  float delta;
  float distanceTmp;
  Vec pIntersec[2];
  Vec vecAux = orig - pos;
  //TODO como paralelizar o calculo de a, b e c com openMP ??
  a = glm::dot(dir, dir);
  b = glm::dot(dir, vecAux)*2.0;
  c = glm::dot(vecAux, vecAux);

  delta = b*b - 4.0*a*c;
  if(delta < 0.0)
    return false;

  pIntersec[0] =  dir*(float)(-b + sqrt(delta))/(2.0f*a) + orig;
  pIntersec[1] =  dir*(float)(-b - sqrt(delta))/(2.0f*a) + orig;

  distance    =  glm::distance(pIntersec[0], orig);
  point = pIntersec[0];

  distanceTmp =  glm::distance(pIntersec[1], orig);
  if(distanceTmp < distance)
  {
    distance = distanceTmp;
    point = pIntersec[1];
  }
  return true;
}
bool Plane::intersectRay(const Vec &orig, const Vec &dir, Vec &point, double &distance)
{
  
  return false;
}
void Sphere::normalAt(const Vec &point, Vec &normal)
{
  normal =  glm::normalize(point-pos);
}
void Plane::normalAt(const Vec &point, Vec &normal)
{
  normal = glm::normalize(this->Normal);
}
