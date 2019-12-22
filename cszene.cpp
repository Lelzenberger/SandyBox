#include "cszene.h"
#include "shader.h"
#include "shadermanager.h"
#include "audioengine.h"
#include "fboproperty.h"
#include "simplecube.h"
#include "texture.h"
#include "QRandomGenerator"
#include "cplane.h"


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

void cSzene::initWorld(float size)
{
    QString path(SRCDIR);
    m_Texture = new Texture(path + QString("/modelstextures/grass.jpg"));
    m_BumpMap = new BumpMap(path + QString("/modelstextures/gravel-bump-map-4k.jpg"));


    m_world = new cWelt();
    m_world->init(m_ShaderWorld, m_PhysicEngine, m_Texture, m_BumpMap, static_cast<int>(size));


    m_tWorld = new Transformation();
    m_tWorld->rotate(-90.0f, 1.0f, 0.0f, 0.0f);

    m_ntWorld = new Node(m_tWorld);
    m_ntWorld->addChild(m_world->getRoot());

    m_Root->addChild(m_ntWorld);

    cPlane * wand1 = new cPlane();
    cPlane * wand2 = new cPlane();
    cPlane * wand3 = new cPlane();
    cPlane * wand4 = new cPlane();

    wand1->init(m_ShaderWorld, m_PhysicEngine, m_Texture, m_BumpMap, size, 3.0f, true);
    wand2->init(m_ShaderWorld, m_PhysicEngine, m_Texture, m_BumpMap, size, 3.0f, true);
    wand3->init(m_ShaderWorld, m_PhysicEngine, m_Texture, m_BumpMap, size, 3.0f, true);
    wand4->init(m_ShaderWorld, m_PhysicEngine, m_Texture, m_BumpMap, size, 3.0f, true);

    Transformation * m_tWand1 = new Transformation();
    Transformation * m_tWand2 = new Transformation();
    Transformation * m_tWand3 = new Transformation();
    Transformation * m_tWand4 = new Transformation();

    m_tWand1->translate(0.0f, 0.0f, size/2.0f);
    m_tWand2->translate(-size/2.0f, 0.0f, 0.0f);
    m_tWand3->translate(0.0f, 0.0f, -size/2.0f);
    m_tWand4->translate(size/2.0f, 0.0f, 0.0f);

    m_tWand1->rotate(0.0f, 0.0f, 0.0f, 0.0f);
    m_tWand2->rotate(90.0f, 0.0f, 1.0f, 0.0f);
    m_tWand3->rotate(180.0f, 0.0f, 1.0f, 0.0f);
    m_tWand4->rotate(270.0f, 0.0f, 1.0f, 0.0f);

    Node * m_ntWand1 = new Node(m_tWand1);
    Node * m_ntWand2 = new Node(m_tWand2);
    Node * m_ntWand3 = new Node(m_tWand3);
    Node * m_ntWand4 = new Node(m_tWand4);

    m_ntWand1->addChild(wand1->getRoot());
    m_ntWand2->addChild(wand2->getRoot());
    m_ntWand3->addChild(wand3->getRoot());
    m_ntWand4->addChild(wand4->getRoot());

    m_Root->addChild(m_ntWand1);
    m_Root->addChild(m_ntWand2);
    m_Root->addChild(m_ntWand3);
    m_Root->addChild(m_ntWand4);
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
        cube[i] = new cWuerfel();
        cube[i]->init(m_Shader, m_PhysicEngine, m_TextureSkyBox);


        m_tCube[i] = new Transformation();
        m_tCube[i]->translate(0, float(i * 1.5f), 0.0f);

        m_ntCube[i] = new Node(m_tCube[i]);
        m_ntCube[i]->addChild(cube[i]->getRoot());

        m_Root->addChild(m_ntCube[i]);
    }
}

void cSzene::initTrees()
{
    QRandomGenerator temp;
    int worldSize = m_world->returnSize()/2;
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
    initWorld(50.0f);
    initTrees();

	
    return m_Root;
}
