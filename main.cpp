#include <iostream>
#include <stdlib.h>     /* atoi */
#include <stdio.h>
#include <GL/glut.h>
#include <raytrace.h>

#define WIDTH 640
#define HEIGHT 480

RayTracer raytracer;
ImageRGBf img(WIDTH,HEIGHT);

void display(void)
{
  int numRefletion = 1;

  raytracer.rayTrace(img, numRefletion);

  glDrawPixels(WIDTH ,HEIGHT,
               GL_RGB, GL_FLOAT, img.data);
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

  //Configurando a matriz de projecao
  raytracer.viewer.setWindowSize(win_width, win_height); //atualiza dimensoes da tela

  //Configurando luz ambiente e background
  raytracer.world.bgColor = Vec(0.0, 0.0, 0.0);
  raytracer.world.lightEnv= 0.6;
  raytracer.world.ka = 0.4;

  // raytracer.world.objs.push_back(new Plane(Material(), Vec(0.0,0.0,10.0) , Vec(0.0, 0.0, -1.0)));
  Material material;
  material.color = Vec(1.0, 0.0, 0.0);
  material.setKs(0.2, 0.4);
  raytracer.world.objs.push_back(new Sphere(material, Vec(0.0,0.0,0.0) , 1.0));

  material.color = Vec(0.0, 1.0, 0.0);
  material.setKs(0.3, 0.4);
  raytracer.world.objs.push_back(new Sphere(material, Vec(2.0,0.0,0.0) , 1.0));

  material.color = Vec(0.0, 0.0, 1.0);
  material.setKs(0.4, 0.4);
  raytracer.world.objs.push_back(new Sphere(material, Vec(0.0, 2.0,0.0), 1.0));

  material.color = Vec(1.0, 0.0, 1.0);
  material.setKs(0.6, 0.4);
  raytracer.world.objs.push_back(new Sphere(material, Vec(0.0, 0.0,2.0), 1.0));
  // raytracer.world.objs.push_back(new Sphere(Material(), Vec(0.0,-2.0,0.0) , 1.0));

  // raytracer.world.lights.push_back( LightSource(Vec(0.0,0.0,0.0), Vec(1.0,0.0,0.0)) );
  raytracer.world.lights.push_back( LightSource(Vec(0.0,10.0,-10.0), Vec(0.7,0.7,0.7)) );
};

void mouse(int button, int state, int x, int y)
{
  static Vec lookAt;

  if (state == GLUT_DOWN)
  {
    raytracer.viewer.pixelToWorld(x, y, lookAt);
    raytracer.viewer.setLookAt(lookAt);
    display();
  }
}

void keyboard (unsigned char key, int x, int y){
  static Vec posCam(0.0, 0.0, -5.0);

  switch (key) {
  case 'a':
    posCam.x++;
    raytracer.viewer.moveCamera(posCam);
    break;
  case 's':
   posCam.z--;
   raytracer.viewer.moveCamera(posCam);
    break;
  case 'd':
   posCam.x--;
   raytracer.viewer.moveCamera(posCam);
    break;
  case 'w':
   posCam.z++;
   raytracer.viewer.moveCamera(posCam);
    break;
  case 'o':
   posCam.y++;
   raytracer.viewer.moveCamera(posCam);
    break;
  case 'l':
   posCam.y--;
   raytracer.viewer.moveCamera(posCam);
    break;
  case 27:
    exit(0);
    break;
  default:
    break;
  }
  display();
}

int main(int argc, char **argv){

  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize (WIDTH, HEIGHT);
  glutInitWindowPosition (0, 0);
  glutCreateWindow ("Ray Tracing Project - UFRN - GC");
  init(WIDTH, HEIGHT);

  glutDisplayFunc(display);
  // glutReshapeFunc(reshape);

  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);

  glutMainLoop();
  return 0;
}
