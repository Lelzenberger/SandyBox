#ifndef CSKYBOX_H
#define CSKYBOX_H

#include "cobjekte.h"
#include "texture.h"
#include "shader.h"

class cSkyBox : public cObjekte
{
    public:
           cSkyBox();
           ~cSkyBox();
           void init(Shader* s, Texture *tex);
    private:
            Texture *m_Texture;
};

#endif // CSKYBOX_H
