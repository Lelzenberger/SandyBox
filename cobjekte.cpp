#include "cobjekte.h"

cObjekte::cObjekte()
{

}
Node cObjekte::getRoot()
{
    return *m_root;
}

Drawable cObjekte::getDrawable()
{
    return *m_drawable;
}

void cObjekte::setMaterialAmbient(float r, float g, float b, float a)
{
    m_material->setAmbient(r, g, b, a);
}

void cObjekte::setMaterialDiffuse(float r, float g, float b, float a)
{
    m_material->setDiffuse(r, g, b, a);
}

void cObjekte::setMaterialSpecular(float r, float g, float b, float a)
{
    m_material->setSpecular(r, g, b, a);
}

void cObjekte::setMaterialEmission(float r, float g, float b, float a)
{
    m_material->setEmission(r, g, b, a);
}

void cObjekte::setMaterialShininess(float s)
{
    m_material->setShininess(s);
}

void cObjekte::init()
{

}

void cObjekte::setShader(Shader *s)
{
    m_shader = s;
}

Drawable * cObjekte::returnDrawable()
{
    return  m_drawable;
}
