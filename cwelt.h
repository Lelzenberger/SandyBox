#ifndef CWELT_H
#define CWELT_H

#include "cobjekte.h"

class cWelt :public cObjekte
{
public:
    cWelt();
    ~cWelt();
    void init(float fSize, Shader* s);
};

#endif // CWELT_H
