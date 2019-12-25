#include "cube.h"
#include "simplecube.h"
#include "shadermanager.h"

Geometry * Cube::m_Geometry = new SimpleCube(1.0f);

Cube::Cube()
{

}

Cube::~Cube()
{

}

void Cube::init(PhysicEngine *physicEngine)
{
    m_Texture = new Texture(SRCDIR + QString("/modelstextures/brickwork-texture"));
    m_BumpMap = new BumpMap(SRCDIR + QString("/modelstextures/brickwork_normal-map"));
    m_Shader = ShaderManager::getShader<Shader>("://shaders/textureLightedBump.vert", "://shaders/textureLightedBump.frag");
    m_PhysicEngine = physicEngine;

    m_Drawable = new Drawable(m_Geometry);
    m_Root = new Node(m_Drawable);

    m_Material = m_Drawable->getProperty<Material>();
    m_Material->setAmbient(0.5f, 0.5f, 0.5f, 1.0f);
    m_Material->setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
    m_Material->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    m_Material->setEmission(0.0f, 0.0f, 0.0f, 1.0f);
    m_Material->setShininess(64.0f);

    m_Drawable->setProperty<Texture>(m_Texture);
    m_Drawable->setProperty<BumpMap>(m_BumpMap);
    m_Drawable->setShader(m_Shader);

    m_PhysicObject = m_PhysicEngine->createNewPhysicObject(m_Drawable);
    m_PhysicObjectConstructionInfo = new PhysicObjectConstructionInfo();
    m_PhysicObjectConstructionInfo->setBoxHalfExtends(QVector3D(0.5f, 0.5f, 0.5f));
    m_PhysicObjectConstructionInfo->setCcdActivation(true);
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
