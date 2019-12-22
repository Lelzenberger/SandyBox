#ifndef CWELT_H
#define CWELT_H

#include "cobjekte.h"
#include "physicengine.h"
#include "texture.h"
#include "bumpmap.h"
#include "shader.h"
#include "ctree.h"
class cWelt :public cObjekte
{
public:
    cWelt(int Size);
    ~cWelt();
    void init(Shader *s, PhysicEngine *pe, Texture *tex, BumpMap *bm);
    int returnSize();

private:
    int fSize;
    Texture *m_Texture;
    BumpMap *m_BumpMap;
};

#endif // CWELT_H
