#ifndef VIEWER_H
#define VIEWER_H

#include <utils.h>

class Camera{
public:
  Vec pos, lookat, vup;
public:
  Camera();
};

class ViewerData{
public:
  Camera camera;
private:
  float  anglePespective;
  float  znear, zfar;
  float  win_width, win_height;

  //atualiza matriz de projecao (para garantir o funcionamento da funcao gluUnProject)
  //deve ser chamada toda vez que algum parametro deste objeto eh atualizado
  void updateMatrix();
public:
  ViewerData(); //default

  void pixelToWorld(const int wx, const int wy, Vec &posWorld);

  void setWindowSize(int win_width, int win_height);
  void setCamera(const Camera &camera);
  void setPespective(float angleP, float znear, float zfar);
};
#endif
