#include "cszene.h"
#include "shader.h"
#include "shadermanager.h"

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
    m_world = new cWelt();
    m_world->init(m_Shader, m_PhysicEngine);

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
    m_Root = new Node();
    m_iPhysicEngineSlot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    m_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(m_iPhysicEngineSlot);
    m_Shader = ShaderManager::getShader<Shader>("://shaders/phongFrag.vert", "://shaders/phongFrag.frag");

    initCubes();
    initSun();
    initWorld();

    return m_Root;
}
