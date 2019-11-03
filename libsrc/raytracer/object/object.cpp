#include <glm/gtx/intersect.hpp>

#include "object.h"

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

void Sphere::intersectLine(const Vec &p0, const Vec &p1, Vec &point, Vec &normal)
{
  static Vec normal2, point2;
  return glm::intersectLineSphere(p0, p1, pos, radius, point, normal
                                  point2, normal2); //WARNING estou retornando apenas a primeira intersecao
}
bool Sphere::intersectRay(const Vec &orig, const Vec &dir, double &distance)
{
  static Vec normal2, point2;
  return glm::intersectLineSphere(p0, p1, pos, radius, point, normal
                                  point2, normal2); //WARNING estou retornando apenas a primeira intersecao
}
void Plane::intersectLine(const Vec &p0, const Vec &p1, Vec &point, Vec &normal)
{

}
bool Plane::intersectRay(const Vec &orig, const Vec &dir, double &distance)
{

}
