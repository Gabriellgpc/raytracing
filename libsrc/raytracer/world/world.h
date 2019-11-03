#include <list>
#include "utils.h"
#include "object.h"

class World{
public:
  std::list<Object*> objs;
  std::list<LightSource> lights;
  Vec   bgColor;
  float lightEnv;

  World();
  World(Vec bgColor, float lightEnv);
  ~World(); //destruir os ponteiros para Object
};
