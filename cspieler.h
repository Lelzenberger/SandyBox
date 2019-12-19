#ifndef CSPIELER_H
#define CSPIELER_H

#include "camera.h"
#include "cameracontroller.h"
#include "keyboardinput.h"

class cSpieler : public CameraController
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
    QVector2D m_mouseMoveVector;

    void isPressed();
    PhysicObject * getObjectInViewDirection();
    void moveObject();
    void scaleObject();
    PhysicObject* v_PhysicObject;
    PhysicObject * ObjectToMove;
    KeyboardInput* keyIn;

protected:
    virtual void controlCamera() override;

};

#endif // CSPIELER_H
