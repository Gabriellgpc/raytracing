#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include "viewerdata.h"

Camera::Camera():
pos(0.0, 0.0, -5.0),
lookat(0.0, 0.0, 0.0),
vup(0.0, 1.0, 0.0)
{

}

void ViewerData::moveCamera(Vec newPosCam)
{
  camera.pos = newPosCam;
  updateMatrix();
}

void ViewerData::updateMatrix()
{
  glViewport(0, 0, (GLsizei)win_width, (GLsizei)win_height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(camera.pos.x,
            camera.pos.y,
            camera.pos.z,
            camera.lookat.x,
            camera.lookat.y,
            camera.lookat.z,
            camera.vup.x,
            camera.vup.y,
            camera.vup.z);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(anglePespective,
                (float)win_width/(float)win_height,
                znear, zfar);
}

ViewerData::ViewerData():
camera(),
anglePespective(60.0),
znear(1.0),
zfar(100.0),
win_width(640),
win_height(480)
{
  updateMatrix();
}

Vec ViewerData::pixelToWorld(const int wx, const int wy)
{
  glLoadIdentity();
  GLdouble rx,ry,rz;
  GLint viewport[4];
  GLdouble mvmatrix[16], projmatrix[16];
  GLint realy;         /*  OpenGL y coordinate position  */

  glGetIntegerv(GL_VIEWPORT, viewport);
  glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
  glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

  realy = viewport[3] - (GLint)wy - 1;

  gluUnProject((GLdouble)wx, (GLdouble)realy, 0.0,
               mvmatrix, projmatrix, viewport,
               &rx,
               &ry,
               &rz);
  return glm::normalize(Vec(rx,ry,rz) - camera.pos);
}


// void ViewerData::pixelToWorld(const int wx, const int wy, Vec &posWorld)
// {
//   glLoadIdentity();
//   GLdouble rx,ry,rz;
//   GLint viewport[4];
//   GLdouble mvmatrix[16], projmatrix[16];
//   GLint realy;         /*  OpenGL y coordinate position  */
//   // updateMatrix();
//   glGetIntegerv(GL_VIEWPORT, viewport);
//   glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
//   glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
//
//   realy = viewport[3] - (GLint)wy - 1;
//
//   gluUnProject((GLdouble)wx, (GLdouble)realy, 0.0,
//                mvmatrix, projmatrix, viewport,
//                &rx,
//                &ry,
//                &rz);
//   posWorld = glm::normalize(Vec(rx,ry,rz) - camera.pos);
// }

void ViewerData::setWindowSize(int win_width, int win_height)
{
  this->win_width = win_width;
  this->win_height= win_height;
  updateMatrix();
}
void ViewerData::setCamera(const Camera &camera)
{
  this->camera.pos    = camera.pos;
  this->camera.lookat = camera.lookat;
  this->camera.vup    = camera.vup;
  updateMatrix();
}
void ViewerData::setPespective(float angleP, float znear, float zfar)
{
  this->anglePespective = angleP;
  this->znear = znear;
  this->zfar  = zfar;
  updateMatrix();
}
void ViewerData::setLookAt(const Vec &at)
{
  this->camera.lookat = at;
  updateMatrix();
}
