#ifndef OWNSCENE_H
#define OWNSCENE_H

#include "node.h"
#include "physicengine.h"
#include "transformation.h"
#include "cube.h"
#include "world.h"
#include "sunlight.h"
#include "audiolistener.h"
#include "soundsource.h"
#include "skybox.h"
#include "tree.h"
#include "QRandomGenerator"
#include "wall.h"

#define cubeCount 15
#define treeCount 30
#define SPAWNRADIUS 6


class OwnScene
{
    public:
            OwnScene();
            ~OwnScene();
            Node *init();
            PhysicEngine *getPhysicEngine();
            SoundSource * getSoundSource();
    private:
            void initWorld();
            void initWall();
            void initSun();
            void initCubes();
            void initSkyBox();
            void initTrees();


            Cube *m_Cubes[cubeCount];
            Tree *m_Tree[treeCount];
            World *m_World;
            Wall *m_Wall;
            SunLight *m_SunLight;
            SkyBox *m_SkyBox;
            Node *m_Root, *m_ntCube[cubeCount],*m_ntTree[treeCount], *m_ntSunLight, *m_nAudio;
            PhysicEngine *m_PhysicEngine;
            int m_iPhysicEngineSlot;      
            Transformation *m_tCube[cubeCount], *m_tTree[treeCount], *m_tSunLight;
            AudioListener *m_AudioListener;
            SoundSource *m_AmbientSound;
            QRandomGenerator temp;

            Shader *m_Shader;
            Texture *m_Texture;
            BumpMap *m_BumpMap;
            Geometry *m_Geometry;
};

#endif
