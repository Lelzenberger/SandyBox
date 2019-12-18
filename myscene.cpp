#include "scenemanager.h"
#include "screenrenderer.h"
#include "mousekeyboardcameracontroller.h"
#include "cszene.h"

Node* initScene1();

void SceneManager::initScenes()
{
    Camera* cam = new Camera();
    CameraController* camController = new MouseKeyboardCameraController(cam);
    camController->setRotSpeed(0.2f);
    camController->setMoveSpeed(0.5f);
    cam->lockZRotation();
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
    return (root);
}
