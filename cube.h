#ifndef CUBE_H
#define CUBE_H

#include "objects.h"

class Cube : public Objects
{
public:
    Cube();
    ~Cube();
    void init(PhysicEngine *physicEngine);
    PhysicObjectConstructionInfo* returnConstructionInfo();
private:
    static Geometry *m_Geometry;
};

#endif
