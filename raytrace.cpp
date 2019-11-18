#include "raytrace.h"

#include <stdio.h>
#include <string.h>
#include <omp.h>

#define PARALLEL

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

void
RayTracer::rayTrace(ImageRGBf &img, int numReflection)const
{
#ifndef PARALLEL
  for(int lin = 0; lin < img.height; lin++)
  {
    for (int col = 0; col < img.width; col++)
    {
      Vec ray_dir = viewer.pixelToWorld(col, lin);
      {
        Vec color = trace(Ray(viewer.camera.pos, ray_dir), numReflection);
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
          shared(img, rayList) firstprivate(numReflection) collapse (2)
  for(int lin = 0; lin < img.height; lin++)
  {
    for (int col = 0; col < img.width; col++)
    {
        Vec color = trace(Ray(viewer.camera.pos, rayList[lin*img.width + col]), numReflection);
        img.setColor(lin, col, color);
    }
  }
  delete[] rayList;
#endif
}


Vec
RayTracer::trace(const Ray ray, int num_reflection)const
{
  Ray  ray_reflected;
  bool reflection;
	Vec  point_intersection;
	Vec  result_color(0.0);
	Object* obj=NULL;


  //Caso base
	//calcular o ponto de intersecao mais proximo
	if(closestPoint(ray, point_intersection, &obj) == false)
    return world.bgColor;

	for(auto &lsource : world.lights)
  {
		result_color += shade(ray,
                          lsource,
                          point_intersection,
                          obj,
                          ray_reflected,
                          reflection);
    if((obj->material.kr != 0.0) && reflection && (num_reflection != 0))
    {
      result_color += obj->material.kr*trace(ray_reflected, num_reflection-1);
    }
	}

  return result_color;
}

bool
RayTracer::closestPoint(/*in*/const Ray ray,
                        /*out*/Vec &point_intersec,
                        /*out*/Object **obj)const
{
	double smallerDistance = MAXDOUBLE;
  bool intersec = false;
  /*itera os objetos, calcula o ponto de inteseccao  e pega o menor deles*/
  for(auto it = world.objs.begin();it != world.objs.end();it++){
    Vec pointTmp;
    double distTmp;
    if((*it)->intersectRay(ray, pointTmp, distTmp)){// ===> TODO
      if( (distTmp < smallerDistance) && (distTmp > 0.0)){
        smallerDistance = distTmp;
        *obj = *it;
        point_intersec = pointTmp;
        intersec = true;
      }
    }
  }
  return intersec;
}


Vec
RayTracer::shade(/*in*/const Ray ray,
                 /*in*/const LightSource &source,
                 /*in*/const Vec point, //ponto sobre a superficie do objeto
                 /*in*/const Object *obj,
                 /*out*/Ray &ray_reflected,
                 /*out*/bool& reflection)const
{
  reflection = false;

	Vec N, L, V, R;
  Vec color;
  Vec tmpP;
  Object* objTmp = NULL;
  //vetor L
  L = glm::normalize(source.pos - point);

  //Observador
  V = -ray.dir;
	//calcula a normal
	obj->normalAt(point, N);
	//raio refletido R
	R = glm::normalize((2.0f*N)*glm::dot(N,L) - L);

  //Equacao de iluminacao
  float fatt = 1.0;
	double cosTetha, cosPhi;

  cosTetha = glm::dot(N,L);
	cosPhi   = glm::dot(R,V);

  #define FABS(x) (((x)<0.0)?-(x):(x))

  cosPhi = FABS(cosPhi);
  if(cosTetha < 0.0)
  {
    // ray_reflected = Ray(point, N);
    return world.getVeclightEnv()*obj->material.color*(obj->material.kd);
  }

  reflection = true;
  ray_reflected = Ray(point, R);
  //testes para considerar objetos entre o ponto e a fonte de luz
  //efeito de sombra
  Ray rayL(point, L);
  double distTmp;
  Vec pointCopy = point;
  if(closestPoint(rayL, tmpP, &objTmp))
  {
    objTmp->intersectRay(rayL, tmpP, distTmp);
    if(  (distTmp < glm::distance(pointCopy, world.lights.begin()->pos )) && (objTmp != obj))
      return world.getVeclightEnv()*obj->material.color*(obj->material.kd);
  }

  // #define SATURADOR(x) (((x) < 0.0)?world.lightEnv*world.ka*obj->material.color[ch]:(x))
  for(int ch = 0; ch < 3; ch++)
  {
    color[ch] = world.lightEnv*world.ka*obj->material.color[ch] +
                fatt*source.color[ch]*(obj->material.kd*obj->material.color[ch]* cosTetha +
                                       obj->material.ks*pow(cosPhi,obj->material.n_shiny));
  }

	return color;
}
