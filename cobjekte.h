#ifndef COBJEKTE_H
#define COBJEKTE_H

#include "drawable.h"
#include "transformation.h"
#include "node.h"
#include "material.h"
#include "shader.h"

class cObjekte : public Drawable
{
public:
    cObjekte();
    Node *getRoot();
    void init();
    void setShader(Shader *s);

protected:
    Node *m_Root;
    Material *m_Material;
    Shader *m_Shader;
    Drawable *m_Drawable;
    PhysicEngine *m_PhysicEngine;
    PhysicObject *m_PhysicObject;
    PhysicObjectConstructionInfo *m_PhysicObjectConstructionInfo;
};

#endif // COBJEKTE_H
