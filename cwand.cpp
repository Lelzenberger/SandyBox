#include "cwand.h"
#include "shadermanager.h"
#include "brickshader.h"

cWand::cWand()
{
    m_rotation = new Transformation();
    m_transformation = new Transformation();
    m_rotateNode = new Node(m_rotation);
    m_transNode = new Node(m_transformation);

    m_transNode->addChild(m_rotateNode);
    m_Root = m_transNode;
}

cWand::~cWand()
{

}


void cWand::init(PhysicEngine *pe, float sizeX, float sizeY)
{
    m_Drawable = new Drawable(new SimplePlane(sizeX, sizeY));
    m_Drawable->setStaticGeometry(true);
    m_rotateNode->addChild(new Node(m_Drawable));
    m_Material = new Material();
    m_Material = m_Drawable->getProperty<Material>();
    m_Material->setAmbient(0.4f, 0.5f, 0.2f, 1.0f);
    m_Material->setDiffuse(0.8f, 1.0f, 0.4f, 1.0f);
    m_Material->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    m_Material->setEmission(0.0f, 0.0f, 0.0f, 1.0f);
    m_Material->setShininess(10.0f);

    m_Drawable->setShader(ShaderManager::getShader<BrickShader>(QString("://shaders/brick.vert"), QString("://shaders/brick.frag")));

    m_PhysicEngine = pe;
    m_PhysicObject = m_PhysicEngine->createNewPhysicObject(m_Drawable);
    m_PhysicObjectConstructionInfo = new PhysicObjectConstructionInfo();
    m_PhysicObjectConstructionInfo->setCollisionHull(CollisionHull::BoxAABB);
    m_PhysicObject->setConstructionInfo(m_PhysicObjectConstructionInfo);
    m_PhysicObject->registerPhysicObject();
}

void cWand::translate(float x, float y, float z)
{
    m_transformation->translate(x,y,z);
}

void cWand::rotate(float angle, QVector3D umDiesenVektorWirdGedreht)
{
    m_rotation->rotate(angle ,umDiesenVektorWirdGedreht);
}


