#include "object.h"

#include <cmath>

static Material Material::randMaterial()
{
  float ks_tmp      = randf();
  float kd_tmp      = 1.0 - ks;
  float n_shiny_tmp = randf() + 1.0;

  return Material(ks_tmp, kd_tmp, n_shiny_tmp, randVec());
}

Material::Material()
{
  *this = Material::randMaterial();
}

Material(const Material &material)
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
  b = 2.0*glm::dot(dir, vecAux);
  c = glm::dot(vecAux, vecAux);

  delta = b*b - 4.0*a*c;
  if(delta < 0.0)
    return false;

  pIntersec[0] = (-b + sqrt(delta))/(2.0*a) * dir + orig;
  pIntersec[1] = (-b - sqrt(delta))/(2.0*a) * dir + orig;

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
