#include "cspieler.h"
#include "inputregistry.h"
#include "openglwidget.h"
#include "scenemanager.h"

cSpieler::cSpieler(Camera * camera) : CameraController(camera)
{
    mFollowMouse = true;
    mRightMouseButtonPressed = true;
    cam = camera;
    cam->lockZRotation();
}

cSpieler::~cSpieler()
{

}


void cSpieler::keyboard(int key, int)
{
    switch(key)
    {
        case 101:
        {

            break;
        }

    }
}
void cSpieler::controlCamera()
{

    //---- KEYBOARD STEUERUNG
    QVector3D deltaPosition;

    KeyboardInput* keyIn = InputRegistry::getInstance().getKeyboardInput();
    if (keyIn->isKeyPressed('w'))
    {
        deltaPosition += mCamera->getViewDir() * mMoveSpeed;
    }
    if (keyIn->isKeyPressed('s'))
    {
        deltaPosition -= mCamera->getViewDir() * mMoveSpeed;
    }
    if (keyIn->isKeyPressed('a'))
    {
        deltaPosition -= mCamera->getRightDir() * mMoveSpeed;
    }
    if (keyIn->isKeyPressed('d'))
    {
        deltaPosition += mCamera->getRightDir() * mMoveSpeed;
    }

    //----- MAUS STEUERUNG
    const QVector2D mouseMoveVector = InputRegistry::getInstance().getMouseInput()->getMouseMove();
//    const QPoint mouseMoveVector2 = InputRegistry::getInstance().getMouseInput()->getMousePosition();
//    qDebug("%i | %i", mouseMoveVector2.x(), mouseMoveVector2.y());

    if (!OpenGLWidget::getInstance()->geometry().contains(OpenGLWidget::getInstance()->mapFromGlobal(QCursor::pos())))
    {

        mFollowMouse = false;
        OpenGLWidget::getInstance()->setCursor(Qt::ArrowCursor);
        return;
    }

    if (InputRegistry::getInstance().getMouseInput()->isMouseButtonPressed(Qt::RightButton))
    {
        if (!mRightMouseButtonPressed)
        {

            mRightMouseButtonPressed = true;
            mFollowMouse = !mFollowMouse;
        }
    }
    else
    {
        mRightMouseButtonPressed = false;
    }

    if (mFollowMouse || SceneManager::instance()->isInFullScreenMode())
    {
        if (SceneManager::instance()->isInFullScreenMode())
        {

            mFollowMouse = false;
        }

        OpenGLWidget& window = *OpenGLWidget::getInstance();
        window.setCursor(Qt::BlankCursor); // Mauszeiger ausblenden
        QRect geometry = window.geometry();
        if (mouseMoveVector.lengthSquared() < geometry.height() * geometry.bottom() / 10.0f)
        {
            mYaw += mouseMoveVector.x() * mRotSpeed;
            mPitch -= mouseMoveVector.y() * mRotSpeed;
            mCamera->setRotation(mYaw, mPitch, 0.f);
        }

        QPoint localCursorPos = window.mapFromGlobal(QCursor::pos());

        geometry.adjust(50, 50, -50, -50);
        if (!geometry.contains(localCursorPos))
        {
            QCursor::setPos(window.mapToGlobal(geometry.center()));
        }
    }
    else
    {
        OpenGLWidget::getInstance()->setCursor(Qt::ArrowCursor);
    }

//     cam->setPosition(cam->getPosition() + deltaPosition * QVector3D(1,0,1));

     cam->setPosition(cam->getPosition().x() + deltaPosition.x(), mHeight,cam->getPosition().z() + deltaPosition.z() );
     cam->setRotation(mYaw, mPitch, mRoll);
}

Camera *cSpieler::getCamera()
{
    return cam;
}
