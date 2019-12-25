#ifndef WORLD_H
#define WORLD_H

#include "objects.h"

class World :public Objects
{
public:
    World();
    ~World();
    void init(PhysicEngine *physicEngine);

private:
    static Geometry *m_Geometry;
};

#endif
