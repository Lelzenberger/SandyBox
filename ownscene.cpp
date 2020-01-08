#include "ownscene.h"
#include "shadermanager.h"
#include "audioengine.h"


#include "simplecube.h"
#include "ownplane.h"

OwnScene::OwnScene()
{

}

OwnScene::~OwnScene()
{

}

PhysicEngine* OwnScene::getPhysicEngine()
{
    return m_PhysicEngine;
}

void OwnScene::initWorld()
{
    m_Texture = new Texture(SRCDIR + QString("/modelstextures/Vol_41_7_Base_Color.png"));
    m_BumpMap = new BumpMap(SRCDIR + QString("/modelstextures/Vol_41_7_Normal.png"));
    m_Shader = ShaderManager::getShader<Shader>("://shaders/textureLightedBump.vert", "://shaders/textureLightedBump.frag");
    m_Geometry = new OwnPlane(50.0f, 50.0f);

    m_World = new World();
    m_World->init(m_PhysicEngine, m_Texture, m_BumpMap, m_Shader, m_Geometry);
    m_Root->addChild(m_World->getRoot());
}

void OwnScene::initWall()
{
    m_Texture = new Texture(SRCDIR + QString("/modelstextures/Vol_41_1_Base_Color.png"));
    m_BumpMap = new BumpMap(SRCDIR + QString("/modelstextures/Vol_41_1_Normal.png"));
    m_Shader = ShaderManager::getShader<Shader>("://shaders/textureLightedBump.vert", "://shaders/textureLightedBump.frag");
    m_Geometry = new OwnPlane(50.0f, 3.0f);

    m_Wall = new Wall();
    m_Wall->init(m_PhysicEngine, m_Texture, m_BumpMap, m_Shader, m_Geometry);
    m_Root->addChild(m_Wall->getRoot());
}

void OwnScene::initSun()
{

    m_SunLight = new SunLight();

    m_SunLight->setAmbient(1.0f, 1.0f, 1.0f);
    m_SunLight->setDiffuse(1.0f, 1.0f, 1.0f);
    m_SunLight->setSpecular(1.0f, 1.0f, 1.0f);
    m_SunLight->turnOn();
    m_tSunLight = new Transformation();
    m_tSunLight->rotate(45.0f, 0.0f, 1.0f, 0.0f);
    m_tSunLight->rotate(-80.0f, 1.0f, 0.0f, 1.0f);
    m_ntSunLight = new Node(m_tSunLight);
    m_ntSunLight->addChild(new Node(m_SunLight));
    m_Root->addChild(m_ntSunLight);

}

void OwnScene::initSkyBox()
{
    m_Texture = new Texture(SRCDIR + QString("/modelstextures/skybox"));
    m_Shader = ShaderManager::getShader<Shader>("://shaders/skybox.vert", "://shaders/texturecube.frag");
    m_Geometry = new SimpleCube(200.0f);

    m_SkyBox = new SkyBox();
    m_SkyBox->init(m_Texture, m_Shader, m_Geometry);
    m_Root->addChild(m_SkyBox->getRoot());
}

void OwnScene::initCubes()
{
    m_Texture = new Texture(SRCDIR + QString("/modelstextures/Vol_41_5_Base_Color.png"));
    m_BumpMap = new BumpMap(SRCDIR + QString("/modelstextures/Vol_41_5_Normal.png"));
    m_Shader = ShaderManager::getShader<Shader>("://shaders/textureLightedBump.vert", "://shaders/textureLightedBump.frag");
    m_Geometry = new SimpleCube(0.8f);

    for (int i = 0; i < cubeCount; i++)
    {
        m_Cubes[i] = new Cube();
        m_Cubes[i]->init(m_PhysicEngine, m_Texture, m_BumpMap, m_Shader, m_Geometry);

        m_tCube[i] = new Transformation();
        m_tCube[i]->translate(0, float(i * 1.5f), 0.0f);

        m_ntCube[i] = new Node(m_tCube[i]);
        m_ntCube[i]->addChild(m_Cubes[i]->getRoot());

        m_Root->addChild(m_ntCube[i]);
    }
}

void OwnScene::initTrees()
{
    temp = QRandomGenerator::securelySeeded();
    int worldSize = 50/2 - 2;
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
        m_Tree[i] = new Tree();
        m_Tree[i]->init(temp.bounded(3,11)*0.2, m_PhysicEngine);                  //RandomSize


        m_tTree[i] = new Transformation();
        m_tTree[i]->translate(X,0,Z);     
        m_ntTree[i] = new Node(m_tTree[i]);
        m_ntTree[i]->addChild(m_Tree[i]->getRoot());

        m_Root->addChild(m_ntTree[i]);
    }


}
Node *OwnScene::init()
{
    m_Root = new Node();
    m_iPhysicEngineSlot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    m_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(m_iPhysicEngineSlot);

    m_AudioListener = new AudioListener();
    m_nAudio = new Node(m_AudioListener);
    AudioEngine::instance().init(AudioEngineType::OpenAL3D);
    m_AmbientSound = new SoundSource(new SoundFile(SRCDIR+QString("/sounds/NatureAmbiance.wav")));
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
