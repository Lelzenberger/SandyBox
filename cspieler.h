#ifndef CSPIELER_H
#define CSPIELER_H

#include "camera.h"
#include "cameracontroller.h"
#include "listener.h"

class cSpieler : public CameraController, public Listener
{
public:
    cSpieler(Camera * camera);
    virtual ~cSpieler();

    void setPhysicEngine(PhysicEngine * PhysicEngine);
    Camera * getCamera();

private:
    Camera * m_cam;
    PhysicEngine * m_PhysicEngine;
    bool m_RightMouseButtonPressed, m_FollowMouse = false;
    const float m_Height = 1.0f;

    void keyboard(int, int) override;
    void getObjectInViewDirection(QVector3D lookDirection);

protected:
    virtual void controlCamera() override;

};

#endif // CSPIELER_H
