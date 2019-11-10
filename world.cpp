#include "world.h"

void World::getVeclightEnv(Vec &c)
{
  float tmpC = lightEnv*ka;
  c = Vec(tmpC, tmpC, tmpC);
}
