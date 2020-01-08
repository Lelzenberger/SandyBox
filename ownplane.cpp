#include "ownplane.h"

OwnPlane::OwnPlane(float width, float heigth)
{
    this->width = width;
    this->height = heigth;

}

OwnPlane::~OwnPlane()
{

}

void OwnPlane::fillVertices(QVector<QVector4D> &vertices)
{
    vertices.clear();
    vertices.append(QVector4D(width / 2.0f, 0.0f, -height / 2.0f, 1.0f));
    vertices.append(QVector4D(width / 2.0f, 0.0f, height / 2.0f, 1.0f));
    vertices.append(QVector4D(-width / 2.0f, 0.0f, height / 2.0f, 1.0f));

    vertices.append(QVector4D(width / 2.0f, 0.0f, -height / 2.0f, 1.0f));
    vertices.append(QVector4D(-width / 2.0f, 0.0f, height / 2.0f, 1.0f));
    vertices.append(QVector4D(-width / 2.0f, 0.0f, -height / 2.0f, 1.0f));
}

void OwnPlane::fillNormals(QVector<QVector3D> &normals, QVector<QVector4D> &vertices)
{
    Q_UNUSED(vertices)
    normals.clear();

    normals.append(QVector3D(0.0f, 1.0f, 0.0f));
    normals.append(QVector3D(0.0f, 1.0f, 0.0f));
    normals.append(QVector3D(0.0f, 1.0f, 0.0f));

    normals.append(QVector3D(0.0f, 1.0f, 0.0f));
    normals.append(QVector3D(0.0f, 1.0f, 0.0f));
    normals.append(QVector3D(0.0f, 1.0f, 0.0f));
}

void OwnPlane::fillTexCoords(QVector<QVector2D> &texCoords)
{
    texCoords.clear();

    texCoords.append(QVector2D(width / 2.0f, -height / 2.0f));
    texCoords.append(QVector2D(width / 2.0f, height / 2.0f));
    texCoords.append(QVector2D(-width / 2.0f, height / 2.0f));

    texCoords.append(QVector2D(width / 2.0f, -height / 2.0f));
    texCoords.append(QVector2D(-width / 2.0f, height / 2.0f));
    texCoords.append(QVector2D(-width / 2.0f, -height / 2.0f));
}

void OwnPlane::fillColors(QVector<QVector4D> &colors)
{
    colors.clear();

    colors.append(QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
    colors.append(QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
    colors.append(QVector4D(1.0f, 1.0f, 1.0f, 1.0f));

    colors.append(QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
    colors.append(QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
    colors.append(QVector4D(1.0f, 1.0f, 1.0f, 1.0f));
}

void OwnPlane::render(Drawable *d)
{
    Q_UNUSED(d)
    glFunctions->glDrawArrays(GL_TRIANGLES, 0, 6);
}
