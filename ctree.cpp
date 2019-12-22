#include "ctree.h"
#include "trianglemesh.h"

TriangleMesh * cTree::m_tmKrone = new TriangleMesh(SRCDIR+QString("/modelstextures/Krone.obj"));
TriangleMesh * cTree::m_tmStamm = new TriangleMesh(SRCDIR+QString("/modelstextures/Baumstamm.obj"));


TriangleMesh * cTree::m_tmKrone = new TriangleMesh(SRCDIR+QString("/modelstextures/Krone.obj"));
TriangleMesh * cTree::m_tmStamm = new TriangleMesh(SRCDIR+QString("/modelstextures/Baumstamm.obj"));

cTree::cTree()
{

}

cTree::~cTree()
{
<<<<<<< HEAD
    m_fScale = fScale*0.06f;
    m_dKrone = new Drawable(m_tmKrone);
    m_dKrone->setStaticGeometry(true);
    m_dStamm = new Drawable(m_tmStamm);
    m_dStamm->setStaticGeometry(true);
    Transformation * t_Scale = new Transformation();
    Transformation * t_Krone = new Transformation();

    t_Krone->translate(0,60,0);
    Node * ntKrone = new Node(t_Krone);

    ntKrone->addChild(new Node(m_dKrone));
    t_Scale->scale(QVector3D(m_fScale,m_fScale,m_fScale));

    m_Root = new Node(t_Scale);
    m_Root->addChild(ntKrone);
    m_Root->addChild(new Node(m_dStamm));
=======
>>>>>>> master

}

void cTree::init(float fScale, PhysicEngine *pe, Shader *s)
{ 
    m_fScale = fScale*0.06f;
    m_Shader = s;
    m_PhysicEngine = pe;

    m_DrawStamm = new Drawable(m_tmStamm);
    m_DrawKrone = new Drawable(m_tmKrone);

    m_MatStamm = m_DrawStamm->getProperty<Material>();
    m_MatStamm->setAmbient(0.27f, 0.13f, 0.03f, 1.0f);
    m_MatStamm->setDiffuse(0.54f, 0.27f, 0.07f, 1.0f);
    m_MatStamm->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    m_MatStamm->setEmission(0.0f, 0.0f, 0.0f, 1.0f);
    m_MatStamm->setShininess(256.0f);

    m_DrawStamm->setShader(m_Shader);

    m_MatKrone = m_DrawKrone->getProperty<Material>();
    m_MatKrone->setAmbient(0.0f, 0.3f, 0.0f, 1.0f);
    m_MatKrone->setDiffuse(0.0f, 0.6f, 0.0f, 1.0f);
    m_MatKrone->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    m_MatKrone->setEmission(0.0f, 0.0f, 0.0f, 1.0f);
    m_MatKrone->setShininess(64.0f);

    m_DrawKrone->setShader(m_Shader);

    m_DrawStamm->setStaticGeometry(true);
    m_DrawKrone->setStaticGeometry(true);

    m_TransKrone = new Transformation();
    m_TransKrone->translate(0.0f, 60.0f, 0.0f);

    m_NodeTransKrone = new Node(m_TransKrone);
    m_NodeTransKrone->addChild(new Node(m_DrawKrone));

    m_TransScale = new Transformation();
    m_TransScale->scale(QVector3D(m_fScale,m_fScale,m_fScale));

    m_NodeTransScale = new Node(m_TransScale);

    m_NodeTransScale->addChild(new Node(m_DrawStamm));
    m_NodeTransScale->addChild(m_NodeTransKrone);

    m_Root = m_NodeTransScale;

    m_PhysicObject = m_PhysicEngine->createNewPhysicObject(m_DrawStamm);
    m_PhysicObjectConstructionInfo= new PhysicObjectConstructionInfo();

    m_PhysicObjectConstructionInfo->setCollisionHull(CollisionHull::BoxAABB);
    m_PhysicObject->setConstructionInfo(m_PhysicObjectConstructionInfo);
    m_PhysicObject->registerPhysicObject();

}
