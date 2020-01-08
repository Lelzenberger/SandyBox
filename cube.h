#ifndef CUBE_H
#define CUBE_H

#include "objects.h"

class Cube : public Objects
{
public:
    Cube();
    ~Cube();
    void init(PhysicEngine *physicEngine, Texture *texture, BumpMap *bumpMap, Shader *shader, Geometry *geometry);
    PhysicObjectConstructionInfo* returnConstructionInfo();
};

#endif
