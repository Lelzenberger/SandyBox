#ifndef CKUGEL_H
#define CKUGEL_H

#include "cobjekte.h"
#include "physicengine.h"

class cKugel : public cObjekte
{
public:
    cKugel();
    ~cKugel();
    void init(Shader* s, PhysicEngine *pe);
};

#endif // CKUGEL_H
