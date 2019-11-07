#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "utils.h"

float
randf()
{
  srand(time(NULL));
  return  rand()/(float)RAND_MAX;
}

Vec
randVec()
{
  return Vec(randf(), randf(), randf());
}

Vec
randPositionInCube(Vec center, int edge)
{
  Vec position;
  position[0] = (edge/2.0)*randf() + center[0];
  position[1] = (edge/2.0)*randf() + center[1];
  position[2] = (edge/2.0)*randf() + center[2];
  return position;
}

// glm::mat4
// rotate(Vec axis, float angle)
// {
//   glm::mat4 trans = glm::mat4(1.0f);
//   return glm::rotate(trans, glm::radians(angle), axis);
// }
