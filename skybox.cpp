#include "skybox.h"
#include "simplecube.h"
#include "shadermanager.h"

SkyBox::SkyBox()
{

}

SkyBox::~SkyBox()
{

}

void SkyBox::init(Texture *texture, Shader *shader, Geometry *geometry)
{
    m_Geometry = geometry;
    m_Texture = texture;
    m_Shader = shader;

    m_Drawable = new Drawable(m_Geometry);
    m_Root = new Node(m_Drawable);

    m_Material = new Material();
    m_Material = m_Drawable->getProperty<Material>();
    m_Material->setAmbient(0.4f, 0.5f, 0.2f, 1.0f);
    m_Material->setDiffuse(0.8f, 1.0f, 0.4f, 1.0f);
    m_Material->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    m_Material->setEmission(0.0f, 0.0f, 0.0f, 1.0f);
    m_Material->setShininess(256.0f);

    m_Drawable->setProperty<Texture>(m_Texture);
    m_Drawable->setShader(m_Shader);
}
