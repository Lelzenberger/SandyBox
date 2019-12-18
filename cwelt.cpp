#include "cwelt.h"
#include "shadermanager.h"
#include "simpleplane.h"

cWelt::cWelt()
{

 }

 cWelt::~cWelt()
 {
     delete m_material;
     delete m_objektNode;
     delete  m_root;
     delete  m_drawable;
 }

 void cWelt::init(float fSize, Shader *s)
 {
     QString path(SRCDIR);
     m_drawable = new Drawable(new SimplePlane(fSize));
     m_root = new Node();
     m_objektNode = new Node( m_drawable);
     m_material = new Material();
     m_material = m_drawable->getProperty<Material>();
     m_shader = s;
     m_drawable->setShader(m_shader);
     m_root->addChild(m_objektNode);
 }
