#include "scenemanager.h"
#include "screenrenderer.h"
#include "mousekeyboardcameracontroller.h"
#include "player.h"
#include "ownscene.h"

Node* initScene1();
Camera * cam;
Player * Spieler;

void SceneManager::initScenes()
{
    cam = new Camera();
    Spieler = new Player(cam);
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
    OwnScene *sz = new OwnScene();
    Node *root = new Node();
    root = sz->init();
    Spieler->setCamera(cam);
    Spieler->setPhysicEngine(sz->getPhysicEngine());
    Spieler->setRoot(root);
    return (root);
}
