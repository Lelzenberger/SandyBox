#ifndef COBJEKTE_H
#define COBJEKTE_H

#include "drawable.h"
#include "transformation.h"
#include "node.h"
#include "material.h"
#include "shader.h"

// amk git
//amk git test2
//amk test git 3
class cObjekte : public Drawable
{
public:
    cObjekte();
    Node getRoot();
    Transformation getTransformation();
protected:
    Node *m_root, *m_transformationNode, *m_objektNode;
    Transformation *m_transformation;
    Material *m_material;
    Shader *m_shader;
};

#endif // COBJEKTE_H
