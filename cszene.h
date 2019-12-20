#ifndef CSZENE_H
#define CSZENE_H

#include "node.h"
#include "physicengine.h"
#include "shader.h"
#include "transformation.h"
#include "cwuerfel.h"
#include "cwelt.h"
#include "csun.h"

#define cubeCount 5

class cSzene
{
    public:
            cSzene();
            ~cSzene();
            Node *init();
            PhysicEngine *getPhysicEngine();

    private:
            void initWorld();
            void initSun();
            void initCubes();
            cWuerfel *cube[cubeCount];
            cWelt *m_world;
            cSun *m_Sun;
            Node *m_Root, *m_ntCube[cubeCount], *m_ntWorld, *m_ntSun;
            PhysicEngine *m_PhysicEngine;
            int m_iPhysicEngineSlot;
            Shader *m_Shader;
            Transformation *m_tCube[cubeCount], *m_tWorld, *m_tSun;
};

#endif // CSZENE_H
