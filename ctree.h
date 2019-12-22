#ifndef CTREE_H
#define CTREE_H
#include "node.h"
#include "drawable.h"
#include "trianglemesh.h"
#include "transformation.h"
#include "cobjekte.h"
#include "physicengine.h"
#include "trianglemesh.h"

class cTree: public cObjekte
{

public:
    cTree();
    void init(float fScale);
    void registerAtPhysicEngine(PhysicEngine * PhysEngine);

private:
   static TriangleMesh * m_tmKrone;
   static TriangleMesh * m_tmStamm;
   float m_fScale;
   Drawable * m_dKrone;
   Drawable * m_dStamm;
};

#endif // CTREE_H
