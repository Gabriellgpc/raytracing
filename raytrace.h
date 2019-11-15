
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

	void rayTrace(ImageRGBf &img, int num_reflection)const;
private:
	//metodos auxiliares
  Vec trace(const Ray ray, int numReflection)const;//Traca um raio saindo de um pixel e retorna uma cor
	bool closestPoint(/*in*/const Ray ray,
                    /*out*/Vec &point_intersec,
                    /*out*/Object **obj)const;//Calcula ponto de intersecao entre o raio e o objeto mais proximo
	Vec shade(/*in*/const Ray ray,
            /*in*/const LightSource &source,
            /*in*/const Vec &point, //ponto sobre a superficie do objeto
            /*in*/const Object *obj,
            /*out*/Ray  &ray_reflected,
            /*out*/bool &reflection)const;   //Aplica a equacao de iluminacao, retorna uma cor
};
#endif//RAYTRACE_H
