#include <cstdio>
#include <iostream>
#include "utils.h"

using namespace std;

int main(int argc, char** argv){
  cout << "Programa teste de Utils\n";

  printf("Randf:%f\n", randf());
  Vec pos = randPositionInCube(Vec(0,0,0), 1.0);
  printf("Pos:(%f,%f,%f)\n", pos[0], pos[1], pos[2]);

  return 0;
}
