#ifndef CWUERFEL_H
#define CWUERFEL_H

#include "cobjekte.h"
#include "simplecube.h"

class cWuerfel : public cObjekte
{
public:
    cWuerfel(float fSize);
    ~cWuerfel();
private:
    Drawable * m_drawable;
};

#endif // CWUERFEL_H
