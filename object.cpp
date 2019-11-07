#include "object.h"
#include <cmath>

Material::Material()
{
  this->ks = 0.35;
  this->kd = 0.35;
  this->n_shiny = 1.5;
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
  Vec dirNorm = glm::normalize(dir);
  //TODO como paralelizar o calculo de a, b e c com openMP ??
  a = 1.0;
  b = glm::dot(dirNorm, vecAux)*2.0;
  c = glm::dot(vecAux, vecAux) - (this->radius*this->radius);

  delta = b*b - 4.0*a*c;
  if(delta < 0.0)
    return false;

  pIntersec[0] =  dirNorm*(float)(-b + sqrt(delta))/(2.0f*a) + orig;
  pIntersec[1] =  dirNorm*(float)(-b - sqrt(delta))/(2.0f*a) + orig;

  distance    =  glm::distance(pIntersec[0], orig);
  point = pIntersec[0];
  distanceTmp =  glm::distance(pIntersec[1], orig);

  distanceTmp = (distanceTmp < 0.0)?-distanceTmp:distanceTmp; //abs
  distance = (distance < 0.0)?-distance:distance; //abs

  if(distanceTmp < distance)
  {
    point = pIntersec[1];
  }
  return true;
}
bool Plane::intersectRay(const Vec &orig, const Vec &dir, Vec &point, double &distance)
{
  //equacao do plano: ax + by + cz + d = 0
  float n_dot_v = glm::dot(Normal, dir);
  float d;
  if(n_dot_v == 0.0)
    return false;
  d = glm::dot(Normal, pos);
  distance = (d + glm::dot(Normal, orig))/n_dot_v;
  point = glm::normalize(dir)*(float)distance + orig;

  distance = (distance < 0.0)?-distance:distance;
  return true;
}

void Sphere::normalAt(const Vec &point, Vec &normal)
{
  normal =  glm::normalize(point-pos);
}
void Plane::normalAt(const Vec &point, Vec &normal)
{
  normal = glm::normalize(this->Normal);
}
