#include "ckugel.h"

#include "shadermanager.h"
#include "simplesphere.h"

cKugel::cKugel()
{
}

void cKugel::init(float fSize, int subX, int subY, Shader* s)
{
    QString path(SRCDIR);
    m_drawable = new Drawable(new SimpleSphere(fSize, subX, subY));
    m_root = new Node();
    m_objektNode = new Node( m_drawable);
    m_material = new Material();
    m_material = m_drawable->getProperty<Material>();
    m_shader = s;
    m_drawable->setShader(m_shader);
    m_root->addChild(m_objektNode);
}

cKugel::~cKugel()
{
    delete m_material;
    delete m_objektNode;
    delete  m_root;
    delete  m_drawable;
}
