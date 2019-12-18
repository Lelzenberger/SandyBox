#include "cwelt.h"
#include "shadermanager.h"

cWelt::cWelt(float fSize)
{
    QString path(SRCDIR);
    m_drawable = new Drawable(new SimplePlane(fSize));
    m_root = new Node();
    m_objektNode = new Node( m_drawable);
    m_transformation = new Transformation();
    m_transformationNode = new Node(m_transformation);
    m_material = new Material();
    m_material = m_drawable->getProperty<Material>();
    m_material->setAmbient(0.4f, 0.5f, 0.2f, 1.0f);
    m_material->setDiffuse(0.8f, 1.0f, 0.4f, 1.0f);
    m_material->setSpecular(1.0f, 1.0f, 1.0f, 1.0f);
    m_material->setEmission(0.0f, 0.0f, 0.0f, 1.0f);
    m_material->setShininess(256.0f);
    m_shader = ShaderManager::getShader<Shader>("://shaders/phongFrag.vert", "://shaders/phongFrag.frag");
    m_drawable->setShader(m_shader);
    m_root->addChild(m_transformationNode);
    m_root->addChild(m_objektNode);
 }

 cWelt::~cWelt()
 {
     delete m_material;
     delete  m_transformationNode;
     delete m_transformation;
     delete m_objektNode;
     delete  m_root;
     delete  m_drawable;
 }
