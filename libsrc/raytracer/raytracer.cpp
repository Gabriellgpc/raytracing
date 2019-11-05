#include "include/raytracer.h"

float &ImageRGBf::operator()(uint i, uint j, uint k){
  uint n = i*width*3 + j*3 + k;
  if(n >= width)return -1;
  return data[n];
};

void RayTracer::rayTrace(ImageRGBf &img,int numRefletion){
  Vec ray;
  //usar OpenMP aqui!
  //WARNING
  // #pragma omp parallel for
  for(int x=0;x<img.width;x++)
  {
    for (int y = 0; y < img.height; y++)
    {
        viewer.pixelDirection2Wolrd(x,y, ray);
        img.setColor(x, y, trace(viewer.camera.pos, ray, numRefletion));
    }
  }
}

Vec Raytracer::trace(const Vec &rayStart,const Vec &rayDir, int numReflection){
	Vec point;
	Vec resultColor,colorTmp;
	Vec orig = rayStarting;
	Vec dir = rayDir;
	double k = 1.0;
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
		closestPoint(orig,dir,point,obj);

		if(obj == NULL/*nao existe intercept point*/)	return word.bgColor;

		k = 1.0/(i*i); // k diminui exponecialmente

		//se intercepta algum obj, calcula a contribuicao de luz para cada fonte
		for(auto &lsource : world.lights){
			//WARNING: acho que vamos ter que tratar essa soma
			resultColor += k*shade(lsource,dirRay,point,obj,colorTmp);
		}
		//calcular a proxima orig e dir
		orig = point;
		//dir = raio refletido
	}
	return resultColor;

}
void Raytracer::closestPoint(const Vec &orig,const Vec &dir,Vec &point,Object * obj)
{
	/*itera os objetos, calcula o ponto de inteseccao  e pega o menor deles*/

	Vec closest(9999999,9999999,999999),normal;
	double smallerDistance=999999;

	for(auto it = world.objs.begin();it != world.objs.end();it++){
		Vec pointTmp;
		double distTmp;
		if((*it)->intersectRay(orig, dir, pointTmp, distTmp)){// ===> TODO
			if(distTmp < smallerDistance){
				smallerDistance = distTmp;
				obj = *it;
				point = pointTmp;
			}
		}
	}
}

Vec Raytracer::shade(LightSource &source, Vec &incidentRay,Vec &point,Object *obj){	
	Vec normal;
	Vec light;

	//calcula a normal
	obj->normalAt(point,normal);

	light = glm::normalize(source.pos-point);

	//raio refletido
	Vec R = (2.0f*normal)*normal.dot(source.pos) - source.pos;

	//usa a equacao de iluminacao

	float fatt = 1.0;//

	double cosTheta,/*theta == angulo da normal com raio refletido     */
		   cosPhi;  /*phi   == angulo da raio refletido com o obsevador*/

	cosTheta = normal.dot(R);
	cosPhi = R.dot(viewer.camera.);

	double IR = world.lightEnv*world.ka + fatt*source.color[0]*(obj->material.kd * cosTetha + obj->material.ks*pow(cosPhi,obj->material.nshiny));	
		
	double IG = world.lightEnv*world.ka + fatt*source.color[1]*(obj->material.kd * cosTetha + obj->material.ks*pow(cosPhi,obj->material.nshiny));	
	double IB = world.lightEnv*world.ka + fatt*source.color[2]*(obj->material.kd * cosTetha + obj->material.ks*pow(cosPhi,obj->material.nshiny));	


	return Vec(IR,IG,IB);
}

