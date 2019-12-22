#ifndef CSUN_H
#define CSUN_H

#include "sunlight.h"
#include "node.h"

class cSun
{
    public:
            cSun();
            ~cSun();
            void init();
             Node *getRoot();
    private:
            SunLight *m_SunLight;
            Node *m_Root;
};

#endif // CSUN_H
