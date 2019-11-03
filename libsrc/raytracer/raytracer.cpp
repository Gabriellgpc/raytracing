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

Vec Raytracer::trace(const Vec &ray, int numReflection){		
	Vec point;
	Vec resultColor;

	//calcular o ponto de intersecao mais proximo
	
	for(int i=0;i< numReflection;i++){
		closestPoint(ray, point);
	}
	
}
void Raytracer::closestPoint(const Vec &ray,Vec &point){
	/*itera os objetos, calcula o ponto de inteseccao  e pega o menor deles*/
	Vec closest = (*world.objs.begin()).pos; 
	for(auto it = world.objs.begin()+1;it != world.objs.end();it++){
		Vec pointTmp;
		if(obj.intersectPoint(){
			if(distanceToCamera(pointTmp) < distanceToCamera(closest)){
				closest = PointTmp;
			}
		}
	}
}
inline double Raytracer::double distanceToCamera(const Vec &point){
	return glm::distance(viewer.camera.pos,point);
}
