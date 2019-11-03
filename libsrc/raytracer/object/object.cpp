#include "object.h"

Material::Material()
{
  *this = Material::randMaterial();
}
