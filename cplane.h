#ifndef CPLANE_H
#define CPLANE_H

#include "cobjekte.h"
#include "physicengine.h"
#include "texture.h"
#include "bumpmap.h"
#include "shader.h"
#include "ctree.h"

class cPlane :public cObjekte
{
public:
    cPlane();
    ~cPlane();
    void init(Shader *s, PhysicEngine *pe, Texture *tex, BumpMap *bm, float sizeX, float sizeY, bool staticGeo);
private:
    Texture *m_Texture;
    BumpMap *m_BumpMap;
};

#endif // CPLANE_H
