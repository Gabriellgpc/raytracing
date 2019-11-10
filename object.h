#ifndef OBJECT_H
#define OBJECT_H

#include <utils.h>

//#############################################################################
class LightSource{
public:
  Vec pos;
  Vec color;

  LightSource(Vec p, Vec c):pos(p), color(c) {}
};

//#############################################################################
class Material{
public:
  //ks: coef. reflexao especular
  //kd: coef. reflexao difusa
  //n_shiny: taxa de espalhamento da reflexao especular (modelo de Phong)
  float ks, kd;
  float n_shiny;
  Vec   color;

  Material();
  Material(const Vec&color);
  Material(const Material &material);
  Material(const float &ks,const float &kd,const float &n_shiny,const Vec &color):
  ks(ks), kd(kd), n_shiny(n_shiny), color(color) {}
  void setKs(float ks, float ka);
};
//#############################################################################

//Classe Abstrata
class Object{
public:
  Vec pos;
  Material material;

  Object():pos(0.0,0.0,0.0), material() {}
  Object(Material mat, Vec pos): material(mat), pos(pos) {}
  virtual bool intersectRay(const Vec &orig, const Vec &dir, Vec &point, double &distance) = 0;
  virtual void normalAt(const Vec &point, Vec &normal) = 0;
};
//#############################################################################

class Sphere:public Object{
public:
  float radius;

  Sphere(Material material, Vec pos, float radius):Object(material, pos), radius(radius) {}
  bool intersectRay(const Vec &orig, const Vec &dir, Vec &point, double &distance);
  void normalAt(const Vec &point, Vec &normal);
};

class Plane:public Object{
public:
  Vec Normal;

  Plane(Material material, Vec pos, Vec normal):Object(material, pos), Normal(glm::normalize(normal)){}
  bool intersectRay(const Vec &orig, const Vec &dir, Vec &point, double &distance);
  void normalAt(const Vec &point, Vec &normal);
};
#endif
