#include "world.h"
#include "ownplane.h"
#include "shadermanager.h"

Geometry * World::m_Geometry = new OwnPlane(50.0f, 50.0f);

World::World()
{

}

World::~World()
{

}

void World::init(PhysicEngine *physicEngine)
{
    m_Texture = new Texture(SRCDIR + QString("/modelstextures/Ground_Grass_001_COLOR.jpg"));
    m_BumpMap = new BumpMap(SRCDIR + QString("/modelstextures/Ground_Grass_001_NORM.jpg"));
    m_Shader = ShaderManager::getShader<Shader>("://shaders/textureLightedBump.vert", "://shaders/textureLightedBump.frag");
    m_PhysicEngine = physicEngine;

    m_Drawable = new Drawable(m_Geometry);
    m_Drawable->setStaticGeometry(true);
    m_Root = new Node(m_Drawable);

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
