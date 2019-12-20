#include "cobjekte.h"

cObjekte::cObjekte()
{

}

Node *cObjekte::getRoot()
{
    return m_Root;
}

void cObjekte::init()
{

}

void cObjekte::setShader(Shader *s)
{
    m_Shader = s;
}
