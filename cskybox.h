#ifndef CSKYBOX_H
#define CSKYBOX_H

#include "objects.h"
#include "texture.h"
#include "shader.h"

class cSkyBox : public Objects
{
    public:
           cSkyBox();
           ~cSkyBox();
           void init(Shader* s, Texture *tex);
    private:
            Texture *m_Texture;
};

#endif // CSKYBOX_H
