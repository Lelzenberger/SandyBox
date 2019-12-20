#ifndef CWUERFEL_H
#define CWUERFEL_H

#include "cobjekte.h"

class cWuerfel : public cObjekte
{
    public:
            cWuerfel();
            ~cWuerfel();
            void init(Shader* s, PhysicEngine *pe);
};

#endif // CWUERFEL_H
