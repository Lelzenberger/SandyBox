#include "cwelt.h"
#include "simpleplane.h"


cWelt::cWelt()
{
}

 cWelt::~cWelt()
 {

 }

 void cWelt::init(Shader *s, PhysicEngine *pe, Texture *tex, BumpMap *bm, int size)
 {

     efSize = size;
     m_Drawable = new Drawable(new SimplePlane(size));
     m_Drawable->setStaticGeometry(true);
     m_Root = new Node(m_Drawable);
     m_Material = new Material();
     m_Material = m_Drawable->getProperty<Material>();
     m_Material->setAmbient(0.4f, 0.5f, 0.2f, 1.0f);
     m_Material->setDiffuse(0.8f, 1.0f, 0.4f, 1.0f);
     m_Material->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
     m_Material->setEmission(0.0f, 0.0f, 0.0f, 1.0f);
     m_Material->setShininess(256.0f);
     m_Shader = s;
     m_BumpMap = bm;
     m_Texture = tex;
     m_Drawable->setProperty<BumpMap>(m_BumpMap);
     m_Drawable->setProperty<Texture>(m_Texture);
     m_Drawable->setShader(m_Shader);
     m_PhysicEngine = pe;
     m_PhysicObject = m_PhysicEngine->createNewPhysicObject(m_Drawable);
     m_PhysicObjectConstructionInfo = new PhysicObjectConstructionInfo();
     m_PhysicObjectConstructionInfo->setCollisionHull(CollisionHull::BoxAABB);
     m_PhysicObject->setConstructionInfo(m_PhysicObjectConstructionInfo);
     m_PhysicObject->registerPhysicObject();
 }

 int cWelt::returnSize()
 {
     return  efSize;
 }
