#ifndef CWAND_H
#define CWAND_H
#include "objects.h"
#include "bumpmap.h"
#include "shader.h"
#include "texture.h"

class cWand : public Objects
{
public:
    cWand();
    ~cWand();
    void init(Shader *s, PhysicEngine *pe, Texture *tex, BumpMap *bm);


private:
    static Geometry * m_Geo;
    Texture *m_Texture;
    BumpMap *m_BumpMap;
    void initWand(float transX, float transZ, QVector3D rotAxis, float angle);
};

#endif // CWAND_H
