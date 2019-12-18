#include "scenemanager.h"
#include "screenrenderer.h"
#include "mousekeyboardcameracontroller.h"
#include "sunlight.h"
#include "cwuerfel.h"
#include "cwelt.h"
#include "transformation.h"
#include "spotlight.h"

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
    QString path(SRCDIR);
    cWuerfel *wuerfel = new cWuerfel(1.0f);
    cWuerfel *sonne = new cWuerfel(1.0f);
    cWelt *welt = new cWelt(200.0f);
    SunLight *sl = new SunLight();
    Transformation *tWelt = new Transformation();
    Transformation *tSl = new Transformation();
    sl->setAmbient(1.0f, 1.0f, 1.0f);
    sl->setDiffuse(1.0f, 1.0f, 1.0f);
    sl->setSpecular(1.0f, 1.0f, 1.0f);
    sl->turnOn();
    tWelt->rotate(-90.0f, 1.0f, 0.0f, 0.0f);
    tSl->translate(-300.0f, 50.0f, 100.0f);
    tSl->rotate(-20.0f, 1.0f, 0.0f, 1.0f);
    tSl->rotate(-45.0f, 0.0f, 1.0f, 0.0f);
    Node *root = new Node();
    Node *wuerfelNode = new Node(wuerfel->getRoot());
    Node *sonneNode = new Node(sonne->getRoot());
    Node *weltNode = new Node(welt->getRoot());
    Node *tWeltNode = new Node(tWelt);
    Node *tSlNode = new Node(tSl);
    tSlNode->addChild(sonneNode);
    Node *slNode = new Node(sl);
    tWeltNode->addChild(weltNode);
    tSlNode->addChild(slNode);
    root->addChild(wuerfelNode);
    root->addChild(tWeltNode);
    root->addChild(tSlNode);
    return (root);
}
