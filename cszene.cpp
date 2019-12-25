#include "cszene.h"
#include "shader.h"
#include "shadermanager.h"
#include "audioengine.h"
#include "fboproperty.h"
#include "simplecube.h"
#include "texture.h"
#include "cplane.h"
#include "cwand.h"

cSzene::cSzene()
{

}

cSzene::~cSzene()
{

}

PhysicEngine* cSzene::getPhysicEngine()
{
    return m_PhysicEngine;
}

void cSzene::initWorld()
{
    m_World = new World();

    m_World->init(m_PhysicEngine);

    m_Root->addChild(m_World->getRoot());
}

void cSzene::initWall()
{
    QString path(SRCDIR);
    m_Texture = new Texture(path + QString("/modelstextures/masonry-wall-texture.jpg"));
    m_BumpMap = new BumpMap(path + QString("/modelstextures/masonry-wall-normal-map.jpg"));

    m_Wall = new cWand();

    m_Wall->init(m_ShaderWorld, m_PhysicEngine, m_Texture, m_BumpMap);

    m_tWall = new Transformation();
    m_ntWall = new Node(m_tWall);
    m_ntWall->addChild(m_Wall->getRoot());

    m_Root->addChild(m_ntWall);
}

void cSzene::initSun()
{

    m_SunLight = new SunLight();

    m_SunLight->setAmbient(1.0f, 1.0f, 1.0f);
    m_SunLight->setDiffuse(1.0f, 1.0f, 1.0f);
    m_SunLight->setSpecular(1.0f, 1.0f, 1.0f);

    m_tSunLight = new Transformation();
    m_tSunLight->rotate(45.0f, 0.0f, 1.0f, 0.0f);
    m_tSunLight->rotate(-80.0f, 1.0f, 0.0f, 1.0f);
    m_ntSunLight = new Node(m_tSunLight);
    m_ntSunLight->addChild(new Node(m_SunLight));
    m_Root->addChild(m_ntSunLight);

}

void cSzene::initSkyBox()
{
    QString path(SRCDIR);
    m_TextureSkyBox = new Texture(path + QString("/modelstextures/skybox"));
    m_SkyBox = new cSkyBox();
    m_SkyBox->init(m_ShaderSkyBox, m_TextureSkyBox);
    m_Root->addChild(m_SkyBox->getRoot());
}

void cSzene::initCubes()
{
    for (int i = 0; i < cubeCount; i++)
    {
        m_Cubes[i] = new Cube();
        m_Cubes[i]->init(m_PhysicEngine);

        m_tCube[i] = new Transformation();
        m_tCube[i]->translate(0, float(i * 1.5f), 0.0f);

        m_ntCube[i] = new Node(m_tCube[i]);
        m_ntCube[i]->addChild(m_Cubes[i]->getRoot());

        m_Root->addChild(m_ntCube[i]);
    }
}

void cSzene::initTrees()
{
    temp = QRandomGenerator::securelySeeded();
    int worldSize = 50/2;
    for (int i = 0; i < treeCount; i++)
    {
        long X = 0;
        long Z = 0;

        while ( X > -SPAWNRADIUS && X < SPAWNRADIUS && Z > -SPAWNRADIUS && Z < SPAWNRADIUS)
        {
            X = temp.bounded(-worldSize,worldSize);
                X = temp.bounded(-worldSize,worldSize);
            Z = temp.bounded(-worldSize,worldSize);
                Z = temp.bounded(-worldSize,worldSize);

                //doppelt damit evtl n bisschen "zeit" vergeht und er nicht dich 2 gleich variablen nimmt? kp ob das was bringt
        }
        tree[i] = new cTree();
        tree[i]->init(temp.bounded(3,11)*0.2, m_PhysicEngine, m_ShaderTree);                  //RandomSize


        m_tTree[i] = new Transformation();
        m_tTree[i]->translate(X,0,Z);
        qDebug("Tree %i : [%i|%i]", i, X,Z);
        m_ntTree[i] = new Node(m_tTree[i]);
        m_ntTree[i]->addChild(tree[i]->getRoot());

        m_Root->addChild(m_ntTree[i]);
    }


}
Node *cSzene::init()
{
    QString path(SRCDIR);
    m_Root = new Node();
    m_iPhysicEngineSlot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    m_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(m_iPhysicEngineSlot);
    m_Shader = ShaderManager::getShader<Shader>("://shaders/phongFrag.vert", "://shaders/phongFrag.frag");
    m_ShaderTree = ShaderManager::getShader<Shader>("://shaders/Stand.vert", "://shaders/Stand.frag");
    m_ShaderWorld = ShaderManager::getShader<Shader>("://shaders/textureLightedBump.vert", "://shaders/textureLightedBump.frag");
    m_ShaderSkyBox = ShaderManager::getShader<Shader>("://shaders/skybox.vert", "://shaders/texturecube.frag");

    m_AudioListener = new AudioListener();
    m_nAudio = new Node(m_AudioListener);
    AudioEngine::instance().init(AudioEngineType::OpenAL3D);
    m_AmbientSound = new SoundSource(new SoundFile(path+QString("/sounds/NatureAmbiance.wav")));
    m_AmbientSound->setLooping(true);
    m_AmbientSound->play();
    m_Root->addChild(m_nAudio);


    initSkyBox();
    initCubes();
    initSun();
    initWorld();
    initWall();
    initTrees();

    return m_Root;
}
