
#ifndef RAYTRACE_H
#define RAYTRACE_H

#include <utils.h>
#include <world.h>
#include <viewerdata.h>

//Classe de imagem em float, util para pintar com glDrawPixels no formato RGB com tipo GL_FLOAT
class ImageRGBf{
public:
  float *data;
  int width, height;
public:
  ImageRGBf();
  ~ImageRGBf();
  ImageRGBf(uint width, uint height);

  void resize(uint newWidth,uint newHeight);
  void setColor(uint i, uint j, const Vec color);
  float operator()(uint i, uint j, uint k);
  //metodo para salvar em bitmap
  // void save(const char**file);
};

class RayTracer{
public:
	World      world;
	ViewerData viewer;
public:
	RayTracer(): world(), viewer(){}
	//Metodo de renderizacao
	//WARNING: levar em conta objetos fora do frustum ??
	void rayTrace(ImageRGBf &img, int numReflection);
private:
	//metodos auxiliares
  Vec trace(const Vec &rayStart,const Vec &rayDir, int numReflection);//Traca um raio saindo de um pixel e retorna uma cor
	bool closestPoint(const Vec &orig,const Vec &dir,Vec &point,Object **obj);//Calcula ponto de intersecao entre o raio e o objeto mais proximo
	Vec shade(LightSource &source,Vec &point,Object *obj,Vec &R);   //Aplica a equacao de iluminacao, retorna uma cor
};
#endif//RAYTRACE_H
