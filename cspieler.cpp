#include "cspieler.h"

cSpieler::cSpieler()
{
    cam = new Camera();
    cam->lockZRotation();

}

cSpieler::~cSpieler()
{

}

void cSpieler::keyboard(int key, int /*modifier*/)
{
    int i = key;
    qDebug("%i",i);
    QVector3D aktuellePos = cam->getPosition();
    QVector3D viewDirection = cam->getViewDir();
    switch (key)
    {
        case 87: //W
            cam->setPosition(aktuellePos + viewDirection * 0.3);
        break;
        case 83: //S
            cam->setPosition(aktuellePos - viewDirection * 0.3);
        break;

        case 65: // A
    {
        QVector3D left;
        left = QVector3D::crossProduct(viewDirection,QVector3D(0,1,0));

            cam->setPosition(aktuellePos - left * 0.2);
        break;
    }
        case 68: //D
        QVector3D left;
        left = QVector3D::crossProduct(viewDirection,QVector3D(0,1,0));

                        cam->setPosition(aktuellePos +left * 0.2);
        break;
    }

}


void cSpieler::setCamera(Camera *camera)
{
    cam = camera;
}

Camera *cSpieler::getCamera()
{
    return cam;
}
