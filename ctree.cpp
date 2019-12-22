#include "ctree.h"

TriangleMesh * cTree::m_tmKrone = new TriangleMesh(SRCDIR+QString("/modelstextures/Krone.obj"));
TriangleMesh * cTree::m_tmStamm = new TriangleMesh(SRCDIR+QString("/modelstextures/Baumstamm.obj"));

cTree::cTree()
{

}

void cTree::init(float fScale)
{
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

}

void cTree::registerAtPhysicEngine(PhysicEngine *PhysEngine)
{
    PhysicObject * m_PhysicObject = PhysEngine->createNewPhysicObject(m_dStamm);
    m_PhysicObjectConstructionInfo = new PhysicObjectConstructionInfo();
    m_PhysicObjectConstructionInfo->setCollisionHull(CollisionHull::BoxAABB);
    m_PhysicObject->setConstructionInfo(m_PhysicObjectConstructionInfo);
    m_PhysicObject->registerPhysicObject();

}
