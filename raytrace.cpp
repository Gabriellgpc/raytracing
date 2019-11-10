#include "raytrace.h"

#include <stdio.h>
#include <string.h>
#include <omp.h>

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
void RayTracer::rayTrace(ImageRGBf &img,int numRefletion){
  static Vec  ray;
    for(int lin = 0; lin < img.height; lin++)
    {
      for (int col = 0; col < img.width; col++)
      {
        viewer.pixelToWorld(col, lin, ray);
        img.setColor(lin, col, trace(viewer.camera.pos, ray, numRefletion));
      }
    }

  // #pragma omp parallel  default(none) shared(img, numRefletion)
  // {
  //   #pragma omp single
  //   for(int lin = 0; lin < img.height; lin++)
  //   {
  //     #pragma omp task default(none)\
  //             shared(img)\
  //             firstprivate(lin, numRefletion)
  //     {
  //       for (int col = 0; col < img.width; col++)
  //       {
  //         Vec ray;
  //         Vec c;
  //         viewer.pixelToWorld(col, lin, ray);
  //         (void)numRefletion;
  //         c = trace(viewer.camera.pos, ray, numRefletion);
  //         img.setColor(lin, col, Vec(0.3, 0.0, 0.3));
  //       }
  //     }
  //   }
  // }
}

Vec RayTracer::trace(const Vec &rayStart,const Vec &rayDir, int numReflection){
	Vec point;
	Vec resultColor;
	Vec orig = rayStart;
	Vec dir = rayDir;
	float k = 1.0;
	Object* obj=NULL;
	/*
	   orig comeca sendo a camera
	   dir comeca sendo o raio lancado pela camera
	   a cada reflexao, orig fica sendo o ponto de inteseccao anterior
	   e dir a direcao do raio refletido
	 */
	for(int i=1;i<= numReflection;i++)
	{
		obj = NULL;

		//calcular o ponto de intersecao mais proximo
		if(closestPoint(orig,dir,point,&obj) == false)
      return world.bgColor;

		k = 1.0/(i*i); // k diminui quadraticamente

    //pre shade
    world.getVeclightEnv(resultColor);
		//se intercepta algum obj, calcula a contribuicao de luz para cada fonte
		for(auto &lsource : world.lights)
    {
			resultColor += k*shade(lsource,point,obj,dir);
		}
		//calcular a proxima orig e dir
		orig = point;
		//dir = (2.0f*normal)*glm::dot(normal,light) - light;
	}
	return resultColor*obj->material.color;
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
        // printf("INTERSECAO dist=%lf\n",distTmp);
				smallerDistance = distTmp;
				*obj = *it;
				point = pointTmp;
        test = true;
        // printf("it = %p\n",*it);
			}
		}
	}
  return test;
}

Vec RayTracer::shade(LightSource &source,Vec &point,Object *obj,Vec &R){
	Vec normal;
	Vec light;

	//calcula a normal
	obj->normalAt(point,normal);

	//vetor L
	light = glm::normalize(source.pos-point);

	//raio refletido R
	Vec reflected = (2.0f*normal)*glm::dot(normal,light) - light;
  R = reflected;
	//usa a equacao de iluminacao

	float fatt = 1.0;//

	double cosTetha,/*theta == angulo da normal com raio refletido     */
		     cosPhi;  /*phi   == angulo da raio refletido com o obsevador*/

	cosTetha = glm::dot(normal,reflected);
	cosPhi = glm::dot(reflected,viewer.camera.pos);

	float IR = fatt*source.color[0]*(obj->material.kd * cosTetha + obj->material.ks*pow(cosPhi,obj->material.n_shiny));
	float IG = fatt*source.color[1]*(obj->material.kd * cosTetha + obj->material.ks*pow(cosPhi,obj->material.n_shiny));
	float IB = fatt*source.color[2]*(obj->material.kd * cosTetha + obj->material.ks*pow(cosPhi,obj->material.n_shiny));

	return Vec(IR, IG, IB);
}
