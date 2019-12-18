#include "scenemanager.h"
#include "screenrenderer.h"
#include "mousekeyboardcameracontroller.h"
#include "cspieler.h"
#include "cszene.h"

Node* initScene1();
Camera * cam = new Camera();

void SceneManager::initScenes()
{
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

    cSpieler* Spieler = new cSpieler();
    Spieler->setCamera(cam);
    cSzene *sz = new cSzene();
    Node *root = new Node();
    root = sz->init();
    return (root);
}
