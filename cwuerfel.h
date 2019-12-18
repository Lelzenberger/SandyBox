#ifndef CWUERFEL_H
#define CWUERFEL_H

#include "cobjekte.h"

class cWuerfel : public cObjekte
{
public:
    cWuerfel();
    ~cWuerfel();
    void init(float fSize, Shader* s);

};

#endif // CWUERFEL_H
