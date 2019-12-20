#include "cwuerfel.h"
#include "simplecube.h"

cWuerfel::cWuerfel()
{

}

cWuerfel::~cWuerfel()
{

}


void cWuerfel::init(Shader* s, PhysicEngine * pe, Texture *tex)
{
    m_Drawable = new Drawable(new SimpleCube(1.0f));
    m_Root = new Node(m_Drawable);
    m_Material = new Material();
    m_Material = m_Drawable->getProperty<Material>();
    m_Material->setAmbient(0.4f, 0.0f, 0.0f, 1.0f);
    m_Material->setDiffuse(0.8f, 0.0f, 0.0f, 1.0f);
    m_Material->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    m_Material->setEmission(0.0f, 0.0f, 0.0f, 1.0f);
    m_Material->setShininess(256.0f);
    m_Shader = s;
    m_Texture = tex;
    m_Drawable->setProperty<Texture>(m_Texture);
    m_Drawable->setShader(m_Shader);
    m_PhysicEngine = pe;
    m_PhysicObject = m_PhysicEngine->createNewPhysicObject(m_Drawable);
    m_PhysicObjectConstructionInfo = new PhysicObjectConstructionInfo();
    m_PhysicObjectConstructionInfo->setBoxHalfExtends(QVector3D(0.5f, 0.5f, 0.5f));
    m_PhysicObjectConstructionInfo->setCcdActivation(false);
    m_PhysicObjectConstructionInfo->setCollisionHull(CollisionHull::BoxHalfExtends);
    m_PhysicObjectConstructionInfo->setFriction(0.5f);
    m_PhysicObjectConstructionInfo->setLocalInertiaPoint(QVector3D(0.f, 0.f, 0.f));
    m_PhysicObjectConstructionInfo->setMass(10.f);
    m_PhysicObjectConstructionInfo->setMidpointTransformation(QMatrix4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
    m_PhysicObjectConstructionInfo->setRestitution(0.1f);
    m_PhysicObjectConstructionInfo->setRollingFriction(0.1f);
    m_PhysicObject->setConstructionInfo(m_PhysicObjectConstructionInfo);
    m_PhysicObject->registerPhysicObject();
}
