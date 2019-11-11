#include "world.h"

void World::getVeclightEnv(Vec &c)
{
  float tmpC = lightEnv*ka;
  c = Vec(tmpC, tmpC, tmpC);
}

Vec World::getVeclightEnv()
{
  float tmpC = lightEnv*ka;
  return Vec(tmpC, tmpC, tmpC);
}

World::~World()
{
  for(auto &obj : objs)
  {
    delete obj;
  }
}
