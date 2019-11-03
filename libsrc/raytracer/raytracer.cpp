#include "include/raytracer.h"

float &ImageRGBf::operator()(uint i, uint j, uint k){
  uint n = i*width*3 + j*3 + k;
  if(n >= width)return -1;
  return data[n];
};

void RayTracer::rayTrace(ImageRGBf &img,int numRefletion){
  Vec ray;
  //usar OpenMP aqui!
  for(int x=0;x<img.width;x++){
    for (int y = 0; y < height; y++) {
        viewer.pixelDirection2Wolrd(x,y, ray);
        img.setColor(x, y, trace(ray, numRefletion));
    }
  }
}
