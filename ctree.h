#ifndef CTREE_H
#define CTREE_H
#include "node.h"
#include "drawable.h"
#include "trianglemesh.h"
#include "transformation.h"
#include "cobjekte.h"
#include "physicengine.h"
#include "trianglemesh.h"
#include "shader.h"


class cTree: public cObjekte
{
    public:
            cTree();
            ~cTree();
            void init(float fScale, PhysicEngine *pe, Shader *s);

    private:
            static TriangleMesh * m_tmKrone;
            static TriangleMesh * m_tmStamm;

            float m_fScale;
            Geometry *m_GeoKrnone, *m_GeoStamm;
            Drawable * m_DrawKrone;
            Drawable * m_DrawStamm;
            Material *m_MatKrone, *m_MatStamm;
            Transformation *m_TransKrone, *m_TransScale;
            Node *m_NodeRoot, *m_NodeKrone, *m_NodeStamm, *m_NodeTransKrone, *m_NodeTransScale;
};

#endif // CTREE_H
