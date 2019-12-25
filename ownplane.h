#ifndef WORLDGEOMETRY_H
#define WORLDGEOMETRY_H

#include "geometry.h"

class OwnPlane : public Geometry
{
public:
    OwnPlane(float width, float height);
    ~OwnPlane();
    virtual void render(Drawable *d) override;

protected:
    virtual void fillVertices(QVector<QVector4D> &vertices) override;
    virtual void fillNormals(QVector<QVector3D> &normals, QVector<QVector4D> &vertices) override;
    virtual void fillTexCoords(QVector<QVector2D> &texCoords) override;
    virtual void fillColors(QVector<QVector4D> &colors) override;

private:
    float width, height;
};

#endif // WORLDGEOMETRY_H
