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
    Camera * getCamera();

private:
    Camera * cam;
    bool mRightMouseButtonPressed, mFollowMouse = false;
    const float mHeight = 1.0f;
    void keyboard(int, int) override;
protected:
    virtual void controlCamera() override;

};

#endif // CSPIELER_H
