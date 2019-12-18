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
    Node getRoot();
    Drawable getDrawable();
    Transformation getTransformation();
    void setMaterialAmbient(float r, float g, float b, float a);
    void setMaterialDiffuse(float r, float g, float b, float a);
    void setMaterialSpecular(float r, float g, float b, float a);
    void setMaterialEmission(float r, float g, float b, float a);
    void setMaterialShininess(float s);
    void init();
    void setShader(Shader *s);

protected:
    Node *m_root, *m_objektNode;
    Material *m_material;
    Shader *m_shader;
    Drawable *m_drawable;
};

#endif // COBJEKTE_H
