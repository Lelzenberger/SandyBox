#ifndef CKUGEL_H
#define CKUGEL_H

#include "cobjekte.h"

class cKugel : public cObjekte
{
public:
    cKugel();
    ~cKugel();
    void init(float fSize, int subX, int subY, Shader* s);
};

#endif // CKUGEL_H
