#ifndef CSZENE_H
#define CSZENE_H

#include "node.h"
#include "physicengine.h"
#include "shader.h"
#include "transformation.h"
#include "cwuerfel.h"
#include "cwelt.h"
#include "sunlight.h"
#include "bumpmap.h"
#include "texture.h"
#include "audiolistener.h"
#include "soundsource.h"
#include "cskybox.h"
#include "ctree.h"
#include "QRandomGenerator"

#define cubeCount 15
#define treeCount 30
#define SPAWNRADIUS 5


class cSzene
{
    public:
            cSzene();
            ~cSzene();
            Node *init();
            PhysicEngine *getPhysicEngine();
            SoundSource * getSoundSource();
    private:
            void initWorld(float size);
            void initSun();
            void initCubes();
            void initSkyBox();
            void initTrees();


            cWuerfel *cube[cubeCount];
            cTree *tree[treeCount];
            cWelt *m_world;
            SunLight *m_SunLight;
            cSkyBox *m_SkyBox;
            Node *m_Root, *m_ntCube[cubeCount],*m_ntTree[treeCount], *m_ntWorld, *m_ntSunLight, *m_nAudio;
            PhysicEngine *m_PhysicEngine;
            int m_iPhysicEngineSlot;
            Shader *m_Shader, *m_ShaderWorld, *m_ShaderSkyBox, *m_ShaderTree;
            Texture *m_Texture, *m_TextureSkyBox;
            BumpMap *m_BumpMap;
            Transformation *m_tCube[cubeCount], *m_tTree[treeCount], *m_tWorld, *m_tSunLight;
            AudioListener *m_AudioListener;
            SoundSource *m_AmbientSound;
            QRandomGenerator temp;
};

#endif // CSZENE_H
