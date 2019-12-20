#ifndef CWUERFEL_H
#define CWUERFEL_H

#include "cobjekte.h"
#include "texture.h"

class cWuerfel : public cObjekte
{
    public:
            cWuerfel();
            ~cWuerfel();
            void init(Shader* s, PhysicEngine *pe, Texture *tex);
    private:
            Texture *m_Texture;
};

#endif // CWUERFEL_H
