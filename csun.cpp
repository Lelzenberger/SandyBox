#include "csun.h"
#include "simplesphere.h"


cSun::cSun()
{

}

cSun::~cSun()
{

}

void cSun::init(Shader *s)
{
    m_SunLight = new SunLight();
    m_SunLight->setAmbient(1.0f, 1.0f, 1.0f);
    m_SunLight->setDiffuse(1.0f, 1.0f, 1.0f);
    m_SunLight->setSpecular(1.0f, 1.0f, 1.0f);

    m_Drawable = new Drawable(new SimpleSphere(1.0f, 10, 10));

    m_Root = new Node(m_Drawable);
    m_Root->addChild(new Node(m_SunLight));

    m_Material = new Material();
    m_Material = m_Drawable->getProperty<Material>();
    m_Material->setAmbient(0.0f, 0.0f, 0.0f, 1.0f);
    m_Material->setDiffuse(0.0f, 0.0f, 0.0f, 1.0f);
    m_Material->setSpecular(0.0f, 0.0f, 0.0f, 1.0f);
    m_Material->setEmission(1.0f, 1.0f, 1.0f, 1.0f);
    m_Material->setShininess(0.0f);

    m_Shader = s;
    m_Drawable->setShader(m_Shader);
}
