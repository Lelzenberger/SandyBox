#ifndef CWAND_H
#define CWAND_H
#include "cobjekte.h"
#include "simpleplane.h"

class cWand : public cObjekte
{
public:
    cWand();
    ~cWand();
    void init(PhysicEngine *pe, float sizeX, float sizeY);
    void translate(float x, float y, float z);
    void rotate(float angle, QVector3D umDiesenVektorWirdGedreht);
private:
    Transformation * m_transformation;
    Transformation * m_rotation;
    Node * m_transNode;
    Node * m_rotateNode;
};

#endif // CWAND_H
