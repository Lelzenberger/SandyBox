#ifndef SKYBOX_H
#define SKYBOX_H

#include "objects.h"

class SkyBox : public Objects
{
public:
        SkyBox();
        ~SkyBox();
        void init(Texture *texture, Shader *shader, Geometry *geometry);
};

#endif
