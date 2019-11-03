#include "utils"
#include "world.h"
#include "viewerdata.h"

//Classe de imagem em float, util para pintar com glDrawPixels no formato RGB com tipo GL_FLOAT
class ImageRGBf{
public:
  float *data;
  uint width, height;

public:
  ImageRGBf();
  ImageRGBf(uint width, uint height);

  void setColor(uint i, uint j, const Vec &color);
  float &operator()(uint i, uint j, uint k);
};

class RayTracer{
public:
  World      world;
  ViewerData viewer;
public:
  RayTracer();
  //Metodo de renderizacao
  //WARNING: levar em conta objetos fora do frustum ??
  void rayTrace(ImageRGBf &img, int numReflection);
private:
  //metodos auxiliares
Vec trace(const Vec &rayStart, Vec &dir, int numReflection);//Traca um raio saindo de um pixel e retorna uma cor
void closestPoint(const Vec &orig,const Vec &dir,Vec &point,Object *obj);//Calcula ponto de intersecao entre o raio e o objeto mais proximo
  void shade(LightSource &source, Vec &incidentRay,Vec &point,Object *obj,Vec &color);   //Aplica a equacao de iluminacao, retorna uma cor

  double distanceToCamera(const Vec &point);
};
