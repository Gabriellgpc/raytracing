#include <list>
#include <utils.h>
#include "../object/object.h"

class World{
public:
  std::list<Object*> objs;
  std::list<LightSource> lights;
  Vec   bgColor;
  float lightEnv;
  float ka;


  World() : bgColor(0.0,0.0,0.0), lightEnv(1.0),ka(0.3){}
  World(Vec bgColor, float lightEnv);
  ~World(); //destruir os ponteiros para Object
};
