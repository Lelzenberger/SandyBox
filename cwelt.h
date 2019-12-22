#ifndef CWELT_H
#define CWELT_H

#include "cobjekte.h"
#include "physicengine.h"
#include "texture.h"
#include "bumpmap.h"
#include "shader.h"
#include "ctree.h"
#include "cplane.h"

class cWelt :public cObjekte
{
public:
    cWelt();
    ~cWelt();
    void init(Shader *s, PhysicEngine *pe, Texture *tex, BumpMap *bm, int size);
	int returnSize();


private:
    int fSize;
    Texture *m_Texture;
    BumpMap *m_BumpMap;
};

#endif // CWELT_H
