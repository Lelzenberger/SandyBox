#ifndef CSPIELER_H
#define CSPIELER_H

#include "camera.h"
#include "listener.h"

class cSpieler : public Listener
{
public:
    cSpieler();
    virtual ~cSpieler();
    Camera * getCamera();
    void setCamera(Camera * cam);
    virtual void keyboard(int key, int modifier);

private:
    Camera * cam;

};

#endif // CSPIELER_H
