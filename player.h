#ifndef PLAYER_H
#define PLAYER_H

#include "camera.h"
#include "cameracontroller.h"
#include "keyboardinput.h"
#include "qelapsedtimer.h"
#include "soundsource.h"
#include "node.h"
#include "drawable.h"


class Player : public CameraController
{
public:
    Player(Camera * camera);
    virtual ~Player();

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
    void checkIfInField();
    Drawable * m_dCrosshair;
    Node * m_rootNode;
    SoundSource * file;
    void playFootStepSound();
    void playItemDropSound();
    void playItemPickUpFailSound();
    SoundSource * m_sPickup, * m_sDrop, * m_sFootstep;

    Camera * m_cam;
    PhysicEngine * m_PhysicEngine;
    bool m_RightMouseButtonPressed, m_FollowMouse = false;
    bool m_bPickedUp, m_bCrosshairFirst = false;
    const float m_Height = 1.0f;
    QVector2D m_mouseMoveVector;
    PhysicObject* v_PhysicObject;
    PhysicObject * ObjectToMove;
    KeyboardInput* keyIn;
    QElapsedTimer timerForScale, timerForSounds, timerForItemDrop;
    PhysicObject * m_PhysicObject;
protected:
    virtual void controlCamera() override;

};

#endif // CSPIELER_H
