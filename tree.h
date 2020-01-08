#ifndef TREE_H
#define TREE_H

#include "node.h"
#include "drawable.h"
#include "trianglemesh.h"
#include "transformation.h"
#include "objects.h"
#include "physicengine.h"
#include "trianglemesh.h"
#include "shader.h"


class Tree: public Objects
{
    public:
            Tree();
            ~Tree();
            void init(float fScale, PhysicEngine *pe);

    private:
            static TriangleMesh * m_tmKrone;
            static TriangleMesh * m_tmStamm;

            float m_fScale;
            Geometry *m_GeoKrnone, *m_GeoStamm;
            Drawable * m_DrawKrone;
            Drawable * m_DrawStamm;
            Material *m_MatKrone, *m_MatStamm;
            Transformation *m_TransScale;
            Node *m_NodeRoot, *m_NodeKrone, *m_NodeStamm, *m_NodeTransKrone, *m_NodeTransScale;
};

#endif // CTREE_H
