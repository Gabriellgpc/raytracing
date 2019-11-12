#include "raytrace.h"

#include <stdio.h>
#include <string.h>
#include <omp.h>

// #define PARALLEL

//height - i - 1 => isso com que o a coordenada na imagem (0,0) seja no canto inferior esquerdo
//isso eh necessario pois eh a referencia do opengl
#define IMG(i,j,c) (data[(height - i - 1)*width*3 + (j)*3 + (c)])
#define MAXDOUBLE 99999999

float ImageRGBf::operator()(uint i, uint j, uint k){
  int n = i*width*3 + j*3 + k;
  if(n >= width) return -1;
  return data[n];
}

ImageRGBf::ImageRGBf(){
  data  = NULL;
  width = 0;
  height= 0;
}

ImageRGBf::ImageRGBf(uint width, uint height){
  // puts("criando img");
  this->width  = width;
  this->height = height;
  data         = new float[width*height*3];
}

ImageRGBf::~ImageRGBf(){
  if(data != NULL)
    delete[] data;
}

void ImageRGBf::resize(uint newWidth,uint newHeight){

  if(data != NULL)
    delete[] data;

  float *newData = new float[newWidth*newHeight*3];

  data = newData;
  this->width = newWidth;
  this->height = newHeight;
}

void ImageRGBf::setColor(uint i, uint j, const Vec color){
  IMG(i, j, 0) = color[0];//set RED
  IMG(i, j, 1) = color[1];//set GREEN
  IMG(i, j, 2) = color[2];//set BLUE
}

void RayTracer::rayTrace(ImageRGBf &img, int numReflection){
#ifndef PARALLEL
  for(int lin = 0; lin < img.height; lin++)
  {
    for (int col = 0; col < img.width; col++)
    {
      Vec ray = viewer.pixelToWorld(col, lin);
      {
        Vec color = trace(viewer.camera.pos, ray, numReflection);
        img.setColor(lin, col, color);
      }
    }
  }
#else
  int size = img.height*img.width;
  Vec *rayList;
  rayList = new Vec[size];

  for(int i = 0; i < img.height; i++)
  for(int j = 0; j < img.width; j++)
  {
    rayList[i*img.width + j] = viewer.pixelToWorld(j, i);
  }

  #pragma omp parallel for schedule(runtime) default(none) \
          shared(img, rayList) firstprivate(numRefletion) collapse (2)
  for(int lin = 0; lin < img.height; lin++)
  {
    for (int col = 0; col < img.width; col++)
    {
      (void)numRefletion;
      {
        Vec color = trace(viewer.camera.pos, rayList[lin*img.width + col], numRefletion);
        img.setColor(lin, col, color);
      }
    }
  }
  delete[] rayList;
#endif
}


Vec RayTracer::trace(const Vec &rayStart,const Vec &rayDir, int numReflection)
{
	Vec point;
	Vec resultColor(0.0);
	Vec orig = rayStart;
	Vec dir = rayDir;
	float k;
	Object* obj=NULL;

  numReflection--;
  //Caso base 1
	//calcular o ponto de intersecao mais proximo
	if(closestPoint(orig,dir,point,&obj) == false)
    return world.bgColor;

	for(auto &lsource : world.lights)
  {
		resultColor += shade(lsource,point,obj,dir);
	}
  // resultColor += world.getVeclightEnv()*obj->material.color;
  //caso base 2

  if(numReflection == 0)
    return resultColor;

  Vec N;
  obj->normalAt(point, N);
  if(glm::dot(N, dir) < 0)
    return resultColor;

  Vec colorRef = trace(point, dir, numReflection);
  resultColor  = (resultColor + colorRef)/2.0f;
  if(colorRef == Vec(0.0))resultColor*=2.0f;
  return resultColor;
}

bool RayTracer::closestPoint(const Vec &orig,const Vec &dir,Vec &point,Object **obj)
{
	double smallerDistance=MAXDOUBLE;
  bool test = false;
  /*itera os objetos, calcula o ponto de inteseccao  e pega o menor deles*/
  for(auto it = world.objs.begin();it != world.objs.end();it++){
    Vec pointTmp;
    double distTmp;
    if((*it)->intersectRay(orig, dir, pointTmp, distTmp)){// ===> TODO
      if(distTmp < smallerDistance){
        smallerDistance = distTmp;
        *obj = *it;
        point = pointTmp;
        test = true;
      }
    }
  }
  return test;
}

Vec RayTracer::shade(LightSource &source,Vec &point,Object *obj,Vec &R){
	Vec N;
	Vec L;
  Vec V;
  Vec color;
  Vec tmpP;
  double tmpDist;
  //vetor L
  L = glm::normalize(source.pos - point);

  //testes para considerar objetos entre o ponto e a fonte de luz
  for(auto it = world.objs.begin();it != world.objs.end();it++)
    if((*it)->intersectRay(point, L, tmpP, tmpDist) && *it != obj)
    {
      if(tmpDist < glm::distance(point, source.pos))
        return world.getVeclightEnv()*obj->material.color;
    }

  //Observador
  V = glm::normalize(viewer.camera.pos - point);
	//calcula a normal
	obj->normalAt(point,N);
	//raio refletido R
	R = (2.0f*N)*glm::dot(N,L) - L;

  //Equacao de iluminacao
	// float fatt = 1.0/(0.00*pow(glm::distance(point, source.pos), 2)+1.0);//
  float fatt = 1.0;
  // float fatt = 1.0/(0.3*pow(glm::distance(point, source.pos), 2)+1.0);//
	double cosTetha, cosPhi;

  cosTetha = glm::dot(N,L);
	cosPhi   = glm::dot(R,V);

  cosTetha = (cosTetha < 0.0)?0.0:cosTetha;
  cosPhi = (cosPhi < 0.0)?0.0:cosPhi;

  for(int ch = 0; ch < 3; ch++)
  {
    color[ch] = world.lightEnv*world.ka*obj->material.color[ch] +
                fatt*source.color[ch]*(obj->material.kd*obj->material.color[ch]* cosTetha +
                                       obj->material.ks*pow(cosPhi,obj->material.n_shiny));
  }

	return color;
}
