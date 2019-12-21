#include "ctree.h"

cTree::cTree()
{
}

void cTree::init(float fScale)
{
    m_fScale = fScale*0.06f;
    m_dKrone = new Drawable(new TriangleMesh(SRCDIR+QString("/modelstextures/Krone.obj")));
    m_dKrone->setStaticGeometry(true);
    m_dStamm = new Drawable(new TriangleMesh(SRCDIR+QString("/modelstextures/Baumstamm.obj")));
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
    //m_Root->addChild(new Node(m_Drawable));
}

void cTree::registerAtPhysicEngine(PhysicEngine *PhysEngine)
{
    PhysicObject * m_PhysicObject = PhysEngine->createNewPhysicObject(m_dStamm);
    m_PhysicObjectConstructionInfo = new PhysicObjectConstructionInfo();
    m_PhysicObjectConstructionInfo->setCollisionHull(CollisionHull::BoxAABB);
    m_PhysicObject->setConstructionInfo(m_PhysicObjectConstructionInfo);
    m_PhysicObject->registerPhysicObject();
}
