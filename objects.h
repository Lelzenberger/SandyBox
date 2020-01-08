#ifndef OBJECTS_H
#define OBJECTS_H

#include "drawable.h"
#include "material.h"
#include "bumpmap.h"

class Objects
{
public:
    Objects();
    ~Objects();
    Node *getRoot();
    void init();

protected:
    Node *m_Root;
    Geometry *m_Geometry;
    Material *m_Material;
    Shader *m_Shader;
    Drawable *m_Drawable;
    Texture *m_Texture;
    BumpMap *m_BumpMap;
    PhysicEngine *m_PhysicEngine;
    PhysicObject *m_PhysicObject;
    PhysicObjectConstructionInfo *m_PhysicObjectConstructionInfo;
};

#endif
