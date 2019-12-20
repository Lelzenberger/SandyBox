#ifndef CWELT_H
#define CWELT_H

#include "cobjekte.h"
#include "physicengine.h"

class cWelt :public cObjekte
{
public:
    cWelt();
    ~cWelt();
    void init(Shader *s, PhysicEngine *pe);
};

#endif // CWELT_H
