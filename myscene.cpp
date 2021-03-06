#include "scenemanager.h"
#include "screenrenderer.h"
#include "mousekeyboardcameracontroller.h"
#include "cspieler.h"
#include "cszene.h"

Node* initScene1();
Camera * cam;
cSpieler * Spieler;
void SceneManager::initScenes()
{
    cam = new Camera();
    Spieler = new cSpieler(cam);
    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    unsigned int myScene = SceneManager::instance()->addScene(initScene1());

    ScreenRenderer* myRenderer = new ScreenRenderer(myContextNr, myScene);
    Q_UNUSED(myRenderer)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
}

Node* initScene1()
{


    cSzene *sz = new cSzene();
    Node *root = new Node();
    root = sz->init();
    Spieler->setCamera(cam);
    Spieler->setPhysicEngine(sz->getPhysicEngine());
    Spieler->setRoot(root);
    return (root);
}
