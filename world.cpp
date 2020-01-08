#include "world.h"
#include "ownplane.h"
#include "shadermanager.h"

World::World()
{

}

World::~World()
{

}

void World::init(PhysicEngine *physicEngine, Texture *texture, BumpMap *bumpMap, Shader *shader, Geometry *geometry)
{
    m_PhysicEngine = physicEngine;
    m_Texture = texture;
    m_BumpMap = bumpMap;
    m_Shader = shader;
    m_Geometry = geometry;

    m_Drawable = new Drawable(m_Geometry);
    m_Drawable->setStaticGeometry(true);
    m_Root = new Node(m_Drawable);

    m_Material = m_Drawable->getProperty<Material>();
    m_Material->setAmbient(0.2f, 0.2f, 0.2f, 1.0f);
    m_Material->setDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
    m_Material->setSpecular(0.1f, 0.1f, 0.1f, 1.0f);
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
