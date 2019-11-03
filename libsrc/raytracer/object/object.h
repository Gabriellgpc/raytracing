#include "utils.h"

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
  Material(const float &ks,const &float kd,const float &n_shiny,const Vec &color):
  ks(ks), kd(kd), n_shiny(n_shiny), color(color) {}

  static Material randMaterial();
};
//#############################################################################

//Classe Abstrata
class Object{
public:
  Vec pos;
  Material material;

  Object(Material material, Vec pos);
  virtual bool intersectPoint(Vec line, Vec &point) = 0;
};

//#############################################################################

class Sphere:public Object{
public:
  float r;

  Sphere(Material material, Vec pos, float r):Object(material, pos), r(r) {}
  bool intersectPoint(Vec line, Vec &point);
};

class Plane:public Object{
public:
  Vec normal;

  Plane(Material material, Vec pos, Vec normal):Object(material, pos), normal(normal){}
  bool intersectPoint(Vec line, Vec &point);
};
