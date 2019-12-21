#ifndef CSZENE_H
#define CSZENE_H

#include "node.h"
#include "physicengine.h"
#include "shader.h"
#include "transformation.h"
#include "cwuerfel.h"
#include "cwelt.h"
#include "csun.h"
#include "bumpmap.h"
#include "texture.h"
#include "audiolistener.h"
#include "soundsource.h"
#include "cskybox.h"

#define cubeCount 5

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
            cWuerfel *cube[cubeCount];
            cWelt *m_world;
            cSun *m_Sun;
            cSkyBox *m_SkyBox;
            Node *m_Root, *m_ntCube[cubeCount], *m_ntWorld, *m_ntSun, *m_nAudio;
            PhysicEngine *m_PhysicEngine;
            int m_iPhysicEngineSlot;
            Shader *m_Shader, *m_ShaderWorld, *m_ShaderSkyBox;
            Texture *m_Texture, *m_TextureSkyBox;
            BumpMap *m_BumpMap;
            Transformation *m_tCube[cubeCount], *m_tWorld, *m_tSun;
            AudioListener *m_AudioListener;
            SoundSource *m_AmbientSound;
            cTree *test;
};

#endif // CSZENE_H
