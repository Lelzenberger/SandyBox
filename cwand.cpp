#include "cwand.h"
#include "shadermanager.h"
#include "ownplane.h"
#include "modeltransformation.h"

Geometry* cWand::m_Geo = new OwnPlane(50.0f, 5.0f);

cWand::cWand()
{

}

cWand::~cWand()
{

}

void cWand::init(Shader *s, PhysicEngine *pe, Texture *tex, BumpMap *bm)
{
    m_Root = new Node();
    m_Shader = s;
    m_BumpMap = bm;
    m_Texture = tex;
    m_PhysicEngine = pe;

    initWand(25.0f, 0.0f, QVector3D(0.0f, 1.0f, 0.0f), -90.0f);
    initWand(0.0f, 25.0f, QVector3D(0.0f, 0.0f, 0.0f), 0.0f);
    initWand(-25.0f, 0.0f, QVector3D(0.0f, 1.0f, 0.0f), 90.0f);
    initWand(0.0f, -25.0f, QVector3D(0.0f, 0.0f, 0.0f), 0.0f);

}

void cWand::initWand(float transX, float transZ, QVector3D rotAxis, float angle)
{
    m_Drawable = new Drawable(m_Geo);
    m_Drawable->setStaticGeometry(true);

    m_Drawable->getProperty<ModelTransformation>()->translate(transX, 0.0f, transZ);
    m_Drawable->getProperty<ModelTransformation>()->rotate(angle, rotAxis);
    m_Drawable->getProperty<ModelTransformation>()->rotate(90.0f, 1.0f, 0.0f, 0.0f);

    m_Root->addChild(new Node(m_Drawable));

    m_Material = new Material();
    m_Material = m_Drawable->getProperty<Material>();
    m_Material->setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
    m_Material->setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
    m_Material->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    m_Material->setEmission(0.0f, 0.0f, 0.0f, 1.0f);
    m_Material->setShininess(64.0f);

    m_Drawable->setProperty<BumpMap>(m_BumpMap);
    m_Drawable->setProperty<Texture>(m_Texture);
    m_Drawable->setShader(m_Shader);

    m_PhysicObject = m_PhysicEngine->createNewPhysicObject(m_Drawable);
    m_PhysicObjectConstructionInfo = new PhysicObjectConstructionInfo();
    m_PhysicObjectConstructionInfo->setCollisionHull(CollisionHull::BoxAABB);
    m_PhysicObject->setConstructionInfo(m_PhysicObjectConstructionInfo);
    m_PhysicObject->registerPhysicObject();
}
