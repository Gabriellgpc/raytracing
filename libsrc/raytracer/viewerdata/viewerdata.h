#include "utils.h"

class Camera{
public:
  Vec pos, lookat, vup;
public:
  Camera();
};

class ViewerData{
private:
  Camera camera;
  float  anglePespective;
  float  znear, zfar;
  float  win_width, win_height;

  //atualiza matriz de projecao (para garantir o funcionamento da funcao gluUnProject)
  //deve ser chamada toda vez que algum parametro deste objeto eh atualizado
  void updateProjection();
public:
  Projection(); //default

  void pixelToWorld(const int& wx, const int& wx, Vec &posWorld);
  void pixelDirection2Wolrd(const int& wx, const int& wx, Vec &versor); //versor saindo do pixel wx,wy apontando para o zfar (util para o raytrace)

  void setWindowSize(int win_width, int win_height);
  void setCamera(const Camera &camera);
  void setPespective(float angleP, float znear, float zfar);
};
