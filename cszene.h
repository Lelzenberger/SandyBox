#ifndef CSZENE_H
#define CSZENE_H
#include "node.h"
#include "physicengine.h"


class cSzene
{
public:
    cSzene();
    Node* init();
    PhysicEngine* getPhysicEngine();
private:
    Node *root;
    PhysicEngine* m_PhysicEngine;
};

#endif // CSZENE_H
