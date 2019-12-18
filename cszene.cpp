#include "cszene.h"
#include "sunlight.h"
#include "cwuerfel.h"
#include "cwelt.h"
#include "transformation.h"
#include "spotlight.h"
#include "shader.h"
#include "shadermanager.h"
#include "ckugel.h"

cSzene::cSzene()
{

}

Node* cSzene::init()
{
    root = new Node();

    QString path(SRCDIR);

    cWuerfel *wuerfel = new cWuerfel();
    Shader *s = ShaderManager::getShader<Shader>("://shaders/phongFrag.vert", "://shaders/phongFrag.frag");
    wuerfel->init(1.0f, s);
    wuerfel->setMaterialAmbient(0.4f, 0.0f, 0.0f, 1.0f);
    wuerfel->setMaterialDiffuse(0.8f, 0.0f, 0.0f, 1.0f);
    wuerfel->setMaterialSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    wuerfel->setMaterialEmission(0.0f, 0.0f, 0.0f, 1.0f);
    wuerfel->setMaterialShininess(256.0f);

    cKugel *sonne = new cKugel();
    sonne->init(1.0f, 25, 25, s);
    sonne->setMaterialAmbient(0.0f, 0.0f, 0.0f, 1.0f);
    sonne->setMaterialDiffuse(0.0f, 0.0f, 0.0f, 1.0f);
    sonne->setMaterialSpecular(0.0f, 0.0f, 0.0f, 1.0f);
    sonne->setMaterialEmission(1.0f, 1.0f, 1.0f, 1.0f);
    sonne->setMaterialShininess(0.0f);

    cWelt *welt = new cWelt();
    welt->init(200.0f, s);
    welt->setMaterialAmbient(0.4f, 0.5f, 0.2f, 1.0f);
    welt->setMaterialDiffuse(0.8f, 1.0f, 0.4f, 1.0f);
    welt->setMaterialSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    welt->setMaterialEmission(0.0f, 0.0f, 0.0f, 1.0f);
    welt->setMaterialShininess(256.0f);

    SunLight *sl = new SunLight();
    Transformation *tWelt = new Transformation();
    Transformation *tSl = new Transformation();
    sl->setAmbient(1.0f, 1.0f, 1.0f);
    sl->setDiffuse(1.0f, 1.0f, 1.0f);
    sl->setSpecular(1.0f, 1.0f, 1.0f);
    sl->turnOn();
    tWelt->rotate(-90.0f, 1.0f, 0.0f, 0.0f);
    tSl->translate(-100.0f, 50.0f, 100.0f);
    tSl->rotate(-20.0f, 1.0f, 0.0f, 1.0f);
    tSl->rotate(-45.0f, 0.0f, 1.0f, 0.0f);

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
    return root;

}
