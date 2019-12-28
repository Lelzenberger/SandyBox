#ifndef WORLD_H
#define WORLD_H

#include "objects.h"

class World :public Objects
{
public:
    World();
    ~World();
    void init(PhysicEngine *physicEngine, Texture *texture, BumpMap *bumpMap, Shader *shader, Geometry *geometry);
};

#endif
