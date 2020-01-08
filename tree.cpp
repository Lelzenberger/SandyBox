#include "tree.h"
#include "trianglemesh.h"
#include "shadermanager.h"
#include "modeltransformation.h"

TriangleMesh * Tree::m_tmKrone = new TriangleMesh(SRCDIR+QString("/modelstextures/Krone.obj"));
TriangleMesh * Tree::m_tmStamm = new TriangleMesh(SRCDIR+QString("/modelstextures/Baumstamm.obj"));

Tree::Tree()
{

}

Tree::~Tree()
{

}

void Tree::init(float fScale, PhysicEngine *physicEngine)
{ 
    m_Shader = ShaderManager::getShader<Shader>("://shaders/Stand.vert", "://shaders/Stand.frag");
    m_fScale = fScale*0.06f;
    m_PhysicEngine = physicEngine;

    m_DrawStamm = new Drawable(m_tmStamm);
    m_DrawKrone = new Drawable(m_tmKrone);

    m_MatStamm = m_DrawStamm->getProperty<Material>();
    m_MatStamm->setAmbient(0.26f, 0.135f, 0.035f, 1.0f);
    m_MatStamm->setDiffuse(0.54f, 0.27f, 0.07f, 1.0f);
    m_MatStamm->setSpecular(0.1f, 0.1f, 0.1f, 1.0f);
    m_MatStamm->setEmission(0.0f, 0.0f, 0.0f, 1.0f);
    m_MatStamm->setShininess(64.0f);

    m_DrawStamm->setShader(m_Shader);

    m_MatKrone = m_DrawKrone->getProperty<Material>();
    m_MatKrone->setAmbient(0.0f, 0.2f, 0.0f, 1.0f);
    m_MatKrone->setDiffuse(0.0f, 0.6f, 0.0f, 1.0f);
    m_MatKrone->setSpecular(0.1f, 0.1f, 0.1f, 1.0f);
    m_MatKrone->setEmission(0.0f, 0.0f, 0.0f, 1.0f);
    m_MatKrone->setShininess(64.0f);

    m_DrawKrone->setShader(m_Shader);

    m_DrawStamm->setStaticGeometry(true);
    m_DrawKrone->setStaticGeometry(true);


    m_DrawKrone->getProperty<ModelTransformation>()->translate(0.0f, 60.0f, 0.0f);


    m_TransScale = new Transformation();
    m_TransScale->scale(QVector3D(m_fScale,m_fScale,m_fScale));

    m_NodeTransScale = new Node(m_TransScale);

    m_NodeTransScale->addChild(new Node(m_DrawStamm));
    m_NodeTransScale->addChild(new Node(m_DrawKrone));

    m_Root = m_NodeTransScale;

    m_PhysicObject = m_PhysicEngine->createNewPhysicObject(m_DrawStamm);
    m_PhysicObjectConstructionInfo= new PhysicObjectConstructionInfo();

    m_PhysicObjectConstructionInfo->setCollisionHull(CollisionHull::BoxAABB);
    m_PhysicObject->setConstructionInfo(m_PhysicObjectConstructionInfo);
    m_PhysicObject->registerPhysicObject();

}
