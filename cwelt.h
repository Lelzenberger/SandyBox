#ifndef CWELT_H
#define CWELT_H


#include "drawable.h"
#include "simpleplane.h"
#include "cobjekte.h"

class cWelt :public cObjekte
{
public:
    cWelt(float fSize);
    ~cWelt();
private:
    Drawable * m_drawable;
};

#endif // CWELT_H
