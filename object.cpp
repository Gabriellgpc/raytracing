#include "object.h"
#include <cmath>

Material::Material()
{
  this->kr = 0.5;
  this->ks = 0.35;
  this->kd = 0.35;
  this->n_shiny = 1.5;
  this->color = randVec();
}

Material::Material(const Vec&color)
{
  this->color = color;
}

Material::Material(const Material &material)
{
  *this = material;
}

void Material::setKs(float ks, float ka)
{
  this->ks = ks;
  this->kd = (1.0 - ka) - ks;
}

bool
Sphere::intersectRay(const Ray &ray, Vec &point, double &distance)const
{
  float b, c, t[2];
  float delta;
  Vec vecAux = ray.orig - pos;

  b = glm::dot(ray.dir, vecAux)*2.0;
  if(b > 0.0 || b == 0.0) //esfera "atras do observador" ou observador dentro da esfera
    return false;
  c = glm::dot(vecAux, vecAux) - (this->radius*this->radius);

  delta = b*b - 4.0f*c;
  if(delta < 0.0)
    return false;
  else if(delta > 0)
  {
    t[0] = (float)(-b + sqrt(delta))/(2.0f);
    t[1] = (float)(-b - sqrt(delta))/(2.0f);

    if(t[0] < t[1])
      distance = t[0];
    else
      distance = t[1];

  }else{
    distance = -b/(2.0f);
  }

  point = ray.orig + ray.dir*(float)distance;

  return true;
}
bool
Plane::intersectRay(const Ray &ray, Vec &point, double &distance)const
{
  //equacao do plano: ax + by + cz + d = 0
  float n_dot_v = glm::dot(Normal, ray.dir);
  float D, t;
  if(n_dot_v == 0.0 || n_dot_v > 1.0) //caso em que não tem intersecao ou que esta 'atras' do plano
    return false;
  D = -glm::dot(Normal, pos);

  t = (-D - glm::dot(Normal, ray.orig))/n_dot_v;
  if(t < 0.0)
    return false;

  point = ray.dir*(float)t + ray.orig;
  distance = t;
  return true;
}

void
Sphere::normalAt(const Vec &point, Vec &normal)const
{
  normal =  glm::normalize(point-pos);
}
void Plane::normalAt(const Vec &point, Vec &normal)const
{
  normal = glm::normalize(this->Normal);
}
