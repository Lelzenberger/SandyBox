#include "csun.h"

cSun::cSun()
{

}

cSun::~cSun()
{

}

void cSun::init()
{
    m_SunLight = new SunLight();
    m_SunLight->setAmbient(1.0f, 1.0f, 1.0f);
    m_SunLight->setDiffuse(1.0f, 1.0f, 1.0f);
    m_SunLight->setSpecular(1.0f, 1.0f, 1.0f);

    m_Root = new Node(m_SunLight);
    //m_Root->addChild(new Node(m_SunLight));
}

Node *cSun::getRoot()
{
    return m_Root;
}
