#include <iostream>
#include <stdlib.h>     /* atoi */

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "raytracer.h"


#define NUM_LIGHT_SRC 2
#define NUM_SPHERES   5
#define NUM_PLANES    3

RayTracer rayTracer;

void display(void)
{
  ImageRGBf img;
  int numRefletion = 2;

  raytracer.rayTrace(img, numRefletion);
  glDrawPixels(rayTracer.viewer.win_width , rayTracer.viewer.win_height,
               GL_RGB, GL_FLOAT, img);
  glutSwapBuffers();
};

void reshape (int w, int h)
{
  rayTracer.viewer.setWindowSize(w, h); //atualiza dimensoes da tela
};

//inicializa o universo
/***** Informacoes para calculo de projecao ****/
/*
* Informacoes ficam em RayTracer.viewerData, essas informacoes possuem um default
* caso nao seja setado apos a construcao de um objeto RayTracer, sera:
* znear(default = 0.01), zfar (default = 10000.0)
* Camera: from(0.0 ,0.0, -0.5), lookAt(0.0, 0.0, 0.0), vUp(0.0, 1.0, 0.0)
* angulo de abertura do pespective (default = 60.0)
* dimensoes da tela: 640x480 ;
* posicionamento e orientacao da Camera;
*/
//Cria e posiciona os Objetos
//Cria e posiciona os pontos de luz
void init(int win_width, int win_height)
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  //Configurando a matriz de projecao
  rayTracer.viewer.setWindowSize(win_width, win_height); //atualiza dimensoes da tela

  //Configurando luz ambiente e background
  rayTracer.world.bgColor = Vec(0.0, 0.0, 0.0);
  rayTracer.world.lightEnv= 0.2;

  //Criando e posicionando objetos e pontos de luz no mundo
  for(int i = 0; i < NUM_SPHERES; i++)
  {
    color    = randVec(1.0);
    pos      = randPositionInCube(VertexA, VertexB);
    material = Material::randMaterial();
    rayTracer.world.objs.push_back(new Sphere(pos, Material::randMaterial(), randf(R_MAX)));
  }

  for(int i = 0; i < NUM_PLANES; i++)
  {
    color    = randVec(1.0);
    pos      = randPositionInCube(VertexA, VertexB);
    material = Material::randMaterial();
    rayTracer.world.objs.push_back(new Plane(pos, Material::randMaterial(), randVec(1.0).normalizze() ));
  }

  for(int i = 0; i < NUM_LIGHT_SRC; i++)
  {
    color    = Vec(1.0, 1.0, 1.0);
    pos      = randPositionInCube(VertexA, VertexB);
    rayTracer.world.lights.push_back( LightSource(pos, color) );
  }

};

int main(int argc, char **argv){
  if(argc != 3){
    std::cerr << "Entrada Esperada: ./main width height\n";
    return -1;
  }
  int width ( atoi(argv[1]) );
  int height( atoi(argv[2]) );

  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (width, height);
  glutInitWindowPosition (100, 100);
  glutCreateWindow ("Ray Tracing Project - UFRN - GC");
  init(width, height);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
}
