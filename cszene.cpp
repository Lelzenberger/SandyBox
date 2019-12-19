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
    root = new Node(new Transformation);

    QString path(SRCDIR);

    int v_Slot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    PhysicEngine* v_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(v_Slot);

    cWuerfel *wuerfel[2];
    Transformation *tWuerfel[2];
    PhysicObject* v_PhysicObjects[2];
    Node* nWuerfel[2];

    Shader *s = ShaderManager::getShader<Shader>("://shaders/phongFrag.vert", "://shaders/phongFrag.frag");

    for (int i = 0; i <= 2; i++)
    {
        tWuerfel[i] = new Transformation();
        tWuerfel[i]->translate(0.0f,((float)i + 0.25f) * 2.f, 0.f);
        Node* tnWuerfel = new Node(tWuerfel[i]);
        root->addChild(tnWuerfel);

        wuerfel[i] = new cWuerfel();
        wuerfel[i]->init(1.0f, s);
        nWuerfel[i] = new Node(wuerfel[i]->getRoot());
        tnWuerfel->addChild(nWuerfel[i]);

        wuerfel[i]->setMaterialAmbient(0.4f, 0.0f, 0.0f, 1.0f);
        wuerfel[i]->setMaterialDiffuse(0.8f, 0.0f, 0.0f, 1.0f);
        wuerfel[i]->setMaterialSpecular(1.0f, 1.0f, 1.0f, 1.0f);
        wuerfel[i]->setMaterialEmission(0.0f, 0.0f, 0.0f, 1.0f);
        wuerfel[i]->setMaterialShininess(256.0f);





        v_PhysicObjects[i] = v_PhysicEngine->createNewPhysicObject(wuerfel[i]);
        PhysicObjectConstructionInfo* v_PhysicObjectConstructionInfo = new PhysicObjectConstructionInfo();
        v_PhysicObjectConstructionInfo->setBoxHalfExtends(QVector3D(0.5f, 0.5f, 0.5f)); // Ausdehnung des Würfels in
                                                                                        // halber länge angeben
        v_PhysicObjectConstructionInfo->setCcdActivation(true); // durchdringen durch andere Objekte Abfangen, benötigt
                                                                // mehr Rechenzeit
        v_PhysicObjectConstructionInfo->setCollisionHull(CollisionHull::BoxHalfExtends); // Form des Hüllkörpers
                                                                                         // festlegen
        v_PhysicObjectConstructionInfo->setFriction(0.5f); // Reibung zwischen 0 und 1 angeben, 0 keine reibung 1
                                                           // maximal
        v_PhysicObjectConstructionInfo->setLocalInertiaPoint(QVector3D(0.f, 0.f, 0.f)); // Schwerpunkt des Objektes
                                                                                        // angeben, Standardwert (0,0,0)
        v_PhysicObjectConstructionInfo->setMass(2.f); // Gewicht des Körpers bestimmen, sollte nicht zu groß gewählt
                                                      // werden
        v_PhysicObjectConstructionInfo->setMidpointTransformation(QMatrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1)); // Mittelpunkttransformation angeben falls
        // Geometrie in seinem Koordinatensystem
        // verschoben liegt
        v_PhysicObjectConstructionInfo->setRestitution(0.1f);     // Elastizität des Körpers bestimmen, von 0 bis 1
                                                                  // definiert
        v_PhysicObjectConstructionInfo->setRollingFriction(0.1f);
        v_PhysicObjects[i]->setConstructionInfo(v_PhysicObjectConstructionInfo);
        v_PhysicObjects[i]->registerPhysicObject();
    }

    cKugel *sonne = new cKugel();
    sonne->init(1.0f, 25, 25, s);
    sonne->setMaterialAmbient(0.0f, 0.0f, 0.0f, 1.0f);
    sonne->setMaterialDiffuse(0.0f, 0.0f, 0.0f, 1.0f);
    sonne->setMaterialSpecular(0.0f, 0.0f, 0.0f, 1.0f);
    sonne->setMaterialEmission(1.0f, 1.0f, 1.0f, 1.0f);
    sonne->setMaterialShininess(0.0f);

    cWelt *welt = new cWelt();
    welt->setStaticGeometry(true);
    welt->init(200.0f, s);
    welt->setMaterialAmbient(0.4f, 0.5f, 0.2f, 1.0f);
    welt->setMaterialDiffuse(0.8f, 1.0f, 0.4f, 1.0f);
    welt->setMaterialSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    welt->setMaterialEmission(0.0f, 0.0f, 0.0f, 1.0f);
    welt->setMaterialShininess(256.0f);
    Transformation *tWelt = new Transformation();
    tWelt->rotate(-90.0f, 1.0f, 0.0f, 0.0f);
    Node* tnWelt = new Node(tWelt);
    Node* nWelt = new Node(welt->getRoot());
    PhysicObject* weltPhys = v_PhysicEngine->createNewPhysicObject(welt);
    PhysicObjectConstructionInfo* constrinfWelt = new PhysicObjectConstructionInfo();
    constrinfWelt->setCollisionHull(CollisionHull::BoxAABB); // Automatische generierung einer Box aus den Vertexpunkten
    weltPhys->setConstructionInfo(constrinfWelt);
    weltPhys->registerPhysicObject();
    tnWelt->addChild(nWelt);


    SunLight *sl = new SunLight();
    Transformation *tSl = new Transformation();
    sl->setAmbient(1.0f, 1.0f, 1.0f);
    sl->setDiffuse(1.0f, 1.0f, 1.0f);
    sl->setSpecular(1.0f, 1.0f, 1.0f);
    sl->turnOn();
    tSl->translate(-100.0f, 50.0f, 100.0f);
    tSl->rotate(-20.0f, 1.0f, 0.0f, 1.0f);
    tSl->rotate(-45.0f, 0.0f, 1.0f, 0.0f);


    Node *sonneNode = new Node(sonne->getRoot());

    Node *tSlNode = new Node(tSl);
    tSlNode->addChild(sonneNode);

    Node *slNode = new Node(sl);
    tSlNode->addChild(slNode);  

    root->addChild(tSlNode);
    root->addChild(tnWelt);
    return root;

}
