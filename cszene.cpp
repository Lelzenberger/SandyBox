#include "cszene.h"
#include "shader.h"
#include "shadermanager.h"
#include "audioengine.h"

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
    QString path(SRCDIR);
    m_Texture = new Texture(path + QString("/modelstextures/gravel-4k.jpg"));
    m_BumpMap = new BumpMap(path + QString("/modelstextures/gravel-bump-map-4k.jpg"));

    m_world = new cWelt();
    m_world->init(m_ShaderWorld, m_PhysicEngine, m_Texture, m_BumpMap);

    m_tWorld = new Transformation();
    m_tWorld->rotate(-90.0f, 1.0f, 0.0f, 0.0f);

    m_ntWorld = new Node(m_tWorld);
    m_ntWorld->addChild(m_world->getRoot());

    m_Root->addChild(m_ntWorld);
}

void cSzene::initSun()
{
    m_Sun = new cSun();
    m_Sun->init(m_Shader);

    m_tSun = new Transformation();
    m_tSun->translate(-100.0f, 50.0f, 100.0f);
    m_tSun->rotate(-20.0f, 1.0f, 0.0f, 1.0f);
    m_tSun->rotate(-45.0f, 0.0f, 1.0f, 0.0f);

    m_ntSun = new Node(m_tSun);
    m_ntSun->addChild(m_Sun->getRoot());

    m_Root->addChild(m_ntSun);
}

void cSzene::initCubes()
{
    for (int i = 0; i < cubeCount; i++)
    {
        cube[i] = new cWuerfel();
        cube[i]->init(m_Shader, m_PhysicEngine);

        m_tCube[i] = new Transformation();
        m_tCube[i]->translate(0.0f,((float)i + 0.25f) * 2.f, 0.f);

        m_ntCube[i] = new Node(m_tCube[i]);
        m_ntCube[i]->addChild(cube[i]->getRoot());

        m_Root->addChild(m_ntCube[i]);
    }
}

Node *cSzene::init()
{
    QString path(SRCDIR);
    m_Root = new Node();
    m_iPhysicEngineSlot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    m_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(m_iPhysicEngineSlot);
    m_Shader = ShaderManager::getShader<Shader>("://shaders/phongFrag.vert", "://shaders/phongFrag.frag");
    m_ShaderWorld = ShaderManager::getShader<Shader>("://shaders/textureLightedBump.vert", "://shaders/textureLightedBump.frag");
    m_AudioListener = new AudioListener();
    m_nAudio = new Node(m_AudioListener);
    AudioEngine::instance().init(AudioEngineType::OpenAL3D);
    m_AmbientSound = new SoundSource(new SoundFile(path+QString("/sounds/NatureAmbiance.wav")));
    m_AmbientSound->setLooping(true);
    m_AmbientSound->play();
    m_Root->addChild(m_nAudio);


    initCubes();
    initSun();
    initWorld();

    return m_Root;
}
