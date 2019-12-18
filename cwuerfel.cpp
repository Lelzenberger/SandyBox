#include "cwuerfel.h"
#include "shadermanager.h"
#include "simplecube.h"

cWuerfel::cWuerfel()
{
}

void cWuerfel::init(float fSize, Shader* s)
{
    QString path(SRCDIR);
    m_drawable = new Drawable(new SimpleCube(fSize));
    m_root = new Node();
    m_objektNode = new Node( m_drawable);
    m_material = new Material();
    m_material = m_drawable->getProperty<Material>();
    m_shader = s;
    m_drawable->setShader(m_shader);
    m_root->addChild(m_objektNode);
}

cWuerfel::~cWuerfel()
{
    delete m_material;
    delete m_objektNode;
    delete  m_root;
    delete  m_drawable;
}
