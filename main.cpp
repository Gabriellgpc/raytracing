#include <iostream>
#include <stdlib.h>     /* atoi */
#include <stdio.h>
#include <GL/glut.h>
#include <raytrace.h>

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <omp.h>

float angX = 0.0;
float angY = 0.0;
float angZ = 0.0;

#define WIDTH 640
#define HEIGHT 480

int numReflection = 0;

RayTracer raytracer;
ImageRGBf img(WIDTH,HEIGHT);

void display(void)
{
  // double start,end, printed;
  // start = omp_get_wtime();
  raytracer.rayTrace(img, numReflection);
  // end = omp_get_wtime();

  glDrawPixels(WIDTH ,HEIGHT,
               GL_RGB, GL_FLOAT, img.data);
  // printed = omp_get_wtime();
  // printf("Raytracer: %fs \t Printed:%fs\n", end - start, printed-end);
  glutSwapBuffers();
};

//inicializa o universo
/***** Informacoes para calculo de projecao ****/
/*
* Informacoes ficam em RayTracer.viewerData, essas informacoes possuem um default
* caso nao seja setado apos a construcao de um objeto RayTracer, sera:
* znear(default = 0.01), zfar (default = 10000.0)
* Camera: from(0.0 ,0.0, -0.5), lookAt(0.0, 0.0, 0.0), vUp(0.0, 1.0, 0.0)
* angulo de abertura do pespective (default = 60.0)
* dimensoes da tela: 640x480;
* posicionamento e orientacao da Camera;
*/
//Cria e posiciona os Objetos
//Cria e posiciona os pontos de luz
void init(int win_width, int win_height)
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  Material material;
  Vec pos;
  float radius = 1.0;

  //Configurando a matriz de projecao
  raytracer.viewer.setWindowSize(win_width, win_height); //atualiza dimensoes da tela
  raytracer.viewer.moveCamera(Vec(0.0, 4.0, -10.0));

  //Configurando luz ambiente e background
  raytracer.world.bgColor = Vec(0, 0, 0);
  raytracer.world.lightEnv= 1.0;
  raytracer.world.ka = 0.0;

  material.n_shiny = 100.0;
  material.color = Vec(1.0, 1.0, 1.0);
  material.setKs(0.5, raytracer.world.ka);
  material.kr = 1.0;
  pos    = Vec(0, 0, 0);
  radius = 2.0;
  raytracer.world.objs.push_back(new Sphere(material, pos, radius));

  material.n_shiny = 10.0;
  material.color = Vec(1.0, 0.0, 0.0);
  material.setKs(0.5, raytracer.world.ka);
  pos    = Vec(-4.0, 0, 0);
  radius = 1.0;
  raytracer.world.objs.push_back(new Sphere(material, pos, radius));

  material.n_shiny = 50.0;
  material.color = Vec(0.0, 1.0, 0.0);
  material.setKs(0.4, raytracer.world.ka);
  pos    = Vec(4.0, 0, 0);
  radius = 1.0;
  raytracer.world.objs.push_back(new Sphere(material, pos, radius));

  material.n_shiny = 10.0;
  material.kr = 0.0;
  material.color = Vec(0.0, 0.0, 1.0);
  material.setKs(0.1, raytracer.world.ka);
  pos    = Vec(0, 0, -4.0);
  radius = 1.0;
  raytracer.world.objs.push_back(new Sphere(material, pos, radius));

  material.n_shiny = 30.0;
  material.kr = 1.0;
  material.color = Vec(1.0, 1.0, 0.0);
  material.setKs(0.1, raytracer.world.ka);
  pos    = Vec(0, 0, 4.0);
  radius = 1.0;
  raytracer.world.objs.push_back(new Sphere(material, pos, radius));

  raytracer.world.lights.push_back( LightSource(Vec(10.0,10.0,-10.0), Vec(1.0,1.0,1.0)));
};

void spinLight()
{
  #define STEP_LIGHT_R 0.02f //5 graus
  static Vec axisY(0.0, 1.0, 0.0);

  glm::vec4 posLight(raytracer.world.lights.begin()->pos, 1.0);
  glm::mat4 model = glm::mat4(1.0f);

  model = glm::rotate(model, STEP_LIGHT_R, axisY);

  posLight = model*posLight;
  Vec aux(posLight.x,posLight.z,posLight.z);
  raytracer.world.lights.begin()->pos = aux;

  display();
}

void keyboard (unsigned char key, int x, int y){

// #define MOVE_LIGHT
#define STEP_R 0.1f //5 graus
#define STEP_D 2.0f
  static Vec axisX(1.0, 0.0, 0.0);
  static Vec axisY(0.0, 1.0, 0.0);
  static Vec axisZ(0.0, 0.0, 1.0);

  glm::vec4 posCam(raytracer.viewer.camera.pos, 1.0);
  glm::vec4 posLight(raytracer.world.lights.begin()->pos, 1.0);
  glm::mat4 model = glm::mat4(1.0f);

  switch (key){
  case 'x':
    model = glm::rotate(model, STEP_R, axisX);
    break;
  case 'y':
    model = glm::rotate(model, STEP_R, axisY);
    break;
  case 'z':
    model = glm::rotate(model, STEP_R, axisZ);
    break;
  case 'X':
    model = glm::rotate(model, -STEP_R, axisX);
    break;
  case 'Y':
    model = glm::rotate(model, -STEP_R, axisY);
    break;
  case 'Z':
    model = glm::rotate(model, -STEP_R, axisZ);
    break;
  case 'd':
#ifndef MOVE_LIGHT
    posCam.z-=STEP_D;
#else

#endif
    break;
  case 'D':
#ifndef MOVE_LIGHT
  posCam.z+=STEP_D;
#else

#endif
    break;
  case 'o':
    posCam= glm::vec4(0.0, 4.0, -10.0, 1.0);
    break;
  case 27:
    exit(0);
    break;
  default:
    break;
  }
#ifndef MOVE_LIGHT
  posCam = model*posCam;
  raytracer.viewer.moveCamera(Vec(posCam.x,posCam.y, posCam.z));
#else
  posLight = model*posLight;
  raytracer.world.lights.begin()->pos = posLight;
#endif

  display();
}

int main(int argc, char **argv)
{
  if(argc == 2)
  {
    numReflection = atoi(argv[1]);
  }
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (WIDTH, HEIGHT);
  glutInitWindowPosition (0, 0);
  glutCreateWindow ("Ray Tracing Project - UFRN - GC");
  init(WIDTH, HEIGHT);

  glutIdleFunc(spinLight);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  glutMainLoop();
  return 0;
}
