#ifndef CSPIELER_H
#define CSPIELER_H

#include "camera.h"
#include "cameracontroller.h"
#include "keyboardinput.h"
#include "qelapsedtimer.h"
#include "soundsource.h"
#include "node.h"
#include "drawable.h"


class cSpieler : public CameraController
{
public:
    cSpieler(Camera * camera);
    virtual ~cSpieler();

    void setRoot(Node* root);
    void setPhysicEngine(PhysicEngine * PhysicEngine);
    Camera * getCamera();

private:
    void isPressed();
    PhysicObject * getObjectInViewDirection();
    void moveObject();
    void scaleObject();
    void createCrosshair();
    void playPickOrDrop(bool DropSound);

    Drawable * m_dCrosshair;
    Node * m_rootNode;
    SoundSource * file;
    Camera * m_cam;
    PhysicEngine * m_PhysicEngine;
    bool m_RightMouseButtonPressed, m_FollowMouse = false;
    bool m_bPickedUp, m_bCrosshairFirst = false;
    const float m_Height = 1.0f;
    QVector2D m_mouseMoveVector;
    PhysicObject* v_PhysicObject;
    PhysicObject * ObjectToMove;
    KeyboardInput* keyIn;
    QElapsedTimer timerForScale;
    QElapsedTimer timerForSound;
    PhysicObject * m_PhysicObject;
protected:
    virtual void controlCamera() override;

};

#endif // CSPIELER_H
