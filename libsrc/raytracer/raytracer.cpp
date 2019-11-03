#include "include/raytracer.h"

float &ImageRGBf::operator()(uint i, uint j, uint k){
  uint n = i*width*3 + j*3 + k;
  if(n >= width)return -1;
  return data[n];
};

void RayTracer::rayTrace(ImageRGBf &img,int numRefletion){
  Vec ray;
  //usar OpenMP aqui!
  #pragma omp parallel for
  for(int x=0;x<img.width;x++)
  {
    for (int y = 0; y < height; y++)
    {
        viewer.pixelDirection2Wolrd(x,y, ray);
        img.setColor(x, y, trace(ray, numRefletion));
    }
  }
}

Vec Raytracer::trace(const Vec &rayStart,const Vec &rayDir, int numReflection){		
	Vec point;
	Vec resultColor,colorTmp;
	Vec orig = rayStarting;
	Vec dir = rayDir;
	double k = 1;
	Object* obj=NULL;
	/*
		orig comeca sendo a camera
		dir comeca sendo o raio lancado pela camera
		a cada reflexao, orig fica sendo o ponto de inteseccao anterior
		e dir a direcao do raio refletido
	 */	
	for(int i=1;i<= numReflection;i++){
		obj = NULL;
			
		//calcular o ponto de intersecao mais proximo
		closestPoint(orig,dir,point,obj);
		
		if(obj == NULL/*nao existe intercept point*/)	return Vec(0,0,0);

		k = 1.0/(i*i); // k diminui exponecialmente

		//se intercepta algum obj, calcula a contribuicao de luz para cada fonte
		for(auto lsource : world.lights){
			//WARNING: acho que vamos ter que tratar essa soma
			resultColor += k*shade(lsource,dirRay,point,obj,colorTmp);
		}
		//calcular a proxima orig e dir
		orig = point;
		//dir = raio refletido
	}
	return resultColor;
	
}
void Raytracer::closestPoint(const Vec &orig,const Vec &dir,Vec &point,Object * obj){
	/*itera os objetos, calcula o ponto de inteseccao  e pega o menor deles*/

	Vec closest(9999999,9999999,999999);
	double smallerDistance=999999;

	for(auto it = world.objs.begin();it != world.objs.end();it++){
		Vec pointTmp;
		double distTmp;
		if((*it)->intersectRay(orig,dir,PointTmp,distTmp)){// ===> TODO
			if(distTmp < smallerDistance){
				closest = PointTmp;
				smallerDistance = distTmp;
				obj = *it;
			}
		}
	}
	point = closest;
}

inline double Raytracer::double distanceToCamera(const Vec &point){
	return glm::distance(viewer.camera.pos,point);
}
