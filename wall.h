#ifndef WALL_H
#define WALL_H

#include "objects.h"

class Wall : public Objects
{
public:
    Wall();
    ~Wall();
    void init(PhysicEngine *physicEngine, Texture *texture, BumpMap *bumpMap, Shader *shader, Geometry *geometry);

private:
    void initWand(float transX, float transZ, QVector3D rotAxis, float angle);
};

#endif
