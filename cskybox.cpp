#include "cskybox.h"
#include "simplecube.h"

cSkyBox::cSkyBox()
{

}

cSkyBox::~cSkyBox()
{

}

void cSkyBox::init(Shader *s, Texture *tex)
{
    m_Drawable = new Drawable(new SimpleCube(200.0f));
    m_Root = new Node(m_Drawable);
    m_Material = new Material();
    m_Material = m_Drawable->getProperty<Material>();
    m_Material->setAmbient(0.4f, 0.5f, 0.2f, 1.0f);
    m_Material->setDiffuse(0.8f, 1.0f, 0.4f, 1.0f);
    m_Material->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    m_Material->setEmission(0.0f, 0.0f, 0.0f, 1.0f);
    m_Material->setShininess(256.0f);
    m_Shader = s;
    m_Texture = tex;
    m_Drawable->setProperty<Texture>(m_Texture);
    m_Drawable->setShader(m_Shader);
}
