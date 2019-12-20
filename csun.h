#ifndef CSUN_H
#define CSUN_H

#include "ckugel.h"
#include "sunlight.h"

class cSun :public cKugel
{
    public:
            cSun();
            ~cSun();
            void init(Shader* s);
    private:
            SunLight *m_SunLight;
};

#endif // CSUN_H
