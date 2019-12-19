#include "cspieler.h"
#include "inputregistry.h"
#include "openglwidget.h"
#include "scenemanager.h"

cSpieler::cSpieler(Camera * camera) : CameraController(camera)
{
    m_PhysicEngine = nullptr;
    m_FollowMouse = true;
    m_RightMouseButtonPressed = true;
    m_cam = camera;
    m_cam->lockZRotation();
    CameraController::setMoveSpeed(0.5f * 0.1f);
}

cSpieler::~cSpieler()
{

}


void cSpieler::setPhysicEngine(PhysicEngine *PhysicEngine)
{
    m_PhysicEngine = PhysicEngine;
}


void cSpieler::getObjectInViewDirection(QVector3D lookDirection)
{
    if ( m_PhysicEngine )
    {
         QVector3D camPos = m_cam->getPosition();
         PhysicObject* v_PhysicObject = m_PhysicEngine->rayTestClosestBody(camPos, camPos + 100 * lookDirection);

         if (v_PhysicObject != 0)
         {
              QMatrix4x4 v_Matrix = v_PhysicObject->getEngineModelMatrix();
              v_Matrix.setColumn(3, (camPos + 10 * lookDirection).toVector4D());
              v_PhysicObject->setEngineModelMatrix(v_Matrix);
              v_PhysicObject->setLinearVelocity(QVector3D(0.f, 0.f, 0.f));
         }
    }
    else
        qDebug("NO PHYSIC ENGINE SET!!");
}


void cSpieler::keyboard(int key, int)
{
    switch(key)
    {
        case 101:
        {
            getObjectInViewDirection(m_cam->getViewDir());
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

    if (!OpenGLWidget::getInstance()->geometry().contains(OpenGLWidget::getInstance()->mapFromGlobal(QCursor::pos())))
    {

        m_FollowMouse = false;
        OpenGLWidget::getInstance()->setCursor(Qt::ArrowCursor);
        return;
    }

    if (InputRegistry::getInstance().getMouseInput()->isMouseButtonPressed(Qt::RightButton))
    {
        if (!m_RightMouseButtonPressed)
        {

            m_RightMouseButtonPressed = true;
            m_FollowMouse = !m_FollowMouse;
        }
    }
    else
    {
        m_RightMouseButtonPressed = false;
    }

    if (m_FollowMouse || SceneManager::instance()->isInFullScreenMode())
    {
        if (SceneManager::instance()->isInFullScreenMode())
        {

            m_FollowMouse = false;
        }

        OpenGLWidget& window = *OpenGLWidget::getInstance();
        window.setCursor(Qt::BlankCursor);
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

     m_cam->setPosition(m_cam->getPosition().x() + deltaPosition.x(), m_Height,m_cam->getPosition().z() + deltaPosition.z() );
     m_cam->setRotation(mYaw, mPitch, mRoll);
}

Camera *cSpieler::getCamera()
{
    return m_cam;
}
