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
    keyIn = InputRegistry::getInstance().getKeyboardInput();
}

cSpieler::~cSpieler()
{

}





void cSpieler::setPhysicEngine(PhysicEngine *PhysicEngine)
{
    m_PhysicEngine = PhysicEngine;
}





PhysicObject* cSpieler::getObjectInViewDirection()
{
    if ( m_PhysicEngine )
    {
         QVector3D camPos = m_cam->getPosition();
         QVector3D lookDirection = m_cam->getViewDir();
         v_PhysicObject = m_PhysicEngine->rayTestClosestBody(camPos, camPos + 100 * lookDirection);
         return v_PhysicObject;
    }
    else
        qDebug("NO PHYSIC ENGINE SET!!");
    return nullptr;
}



void cSpieler::moveObject()
{
    ObjectToMove = getObjectInViewDirection();

    if ( ObjectToMove != nullptr )
    {
        QVector3D camPos = m_cam->getPosition();
        QVector3D lookDirection = m_cam->getViewDir();

        QMatrix4x4 matrixObjekt = ObjectToMove->getEngineModelMatrix();
        matrixObjekt.setColumn(3, (camPos + 5 * lookDirection).toVector4D());
        ObjectToMove->setEngineModelMatrix(matrixObjekt);
        ObjectToMove->setLinearVelocity(QVector3D(0.f, 0.f, 0.f));
    }

}

void cSpieler::scaleObject()
{
    ObjectToMove = getObjectInViewDirection();

     if ( ObjectToMove != nullptr  )
     {
        QMatrix4x4 Scale = QMatrix4x4(5,0,0,0,
                                      0,5,0,0,
                                      0,0,5,0,
                                      0,0,0,5);
        QMatrix4x4 matrixObjekt = ObjectToMove->getEngineModelMatrix();
        matrixObjekt =   Scale * matrixObjekt ;
        ObjectToMove->setEngineModelMatrix(matrixObjekt);
    }
}


void cSpieler::isPressed()
{
    if (keyIn->isKeyPressed('e'))
    {
        moveObject();
    }
    if (keyIn->isKeyPressed('q'))
    {
        scaleObject();
    }
}


void cSpieler::controlCamera()
{

    isPressed();
//---- KEYBOARD STEUERUNG
    QVector3D deltaPosition;

    keyIn = InputRegistry::getInstance().getKeyboardInput();
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
    m_mouseMoveVector = InputRegistry::getInstance().getMouseInput()->getMouseMove();

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
        if (m_mouseMoveVector.lengthSquared() < geometry.height() * geometry.bottom() / 10.0f)
        {
            mYaw += m_mouseMoveVector.x() * mRotSpeed;
            mPitch -= m_mouseMoveVector.y() * mRotSpeed;
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

}

Camera *cSpieler::getCamera()
{
    return m_cam;
}
