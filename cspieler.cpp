#include "cspieler.h"
#include "inputregistry.h"
#include "openglwidget.h"
#include "scenemanager.h"

cSpieler::cSpieler(Camera * camera) : CameraController(camera)
{
    QString path(SRCDIR);

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

        if ( ObjectToMove != nullptr && ObjectToMove->getPhysicState() == PhysicState::Dynamic)
        {
            QVector3D camPos = m_cam->getPosition();
            QVector3D lookDirection = m_cam->getViewDir();

            QMatrix4x4 matrixObjekt = ObjectToMove->getEngineModelMatrix();
            matrixObjekt.setColumn(3, (camPos + 4 * lookDirection).toVector4D());
            ObjectToMove->setEngineModelMatrix(matrixObjekt);
            ObjectToMove->setLinearVelocity(QVector3D(0.f, 0.f, 0.f));

            if ( !m_bPickedUp )
            {
                m_bPickedUp = !m_bPickedUp;
                int i = timerForScale.elapsed() % 4 ;
                switch(i)
                {

                    case 0:

                        m_sPickup = new SoundSource(new SoundFile(SRCDIR+QString("/sounds/pickup1.wav")));
                        m_sPickup->play();
                        break;

                    case 1:

                        m_sPickup = new SoundSource(new SoundFile(SRCDIR+QString("/sounds/pickup2.wav")));
                        m_sPickup->play();
                        break;

                    case 2:
                        m_sPickup = new SoundSource(new SoundFile(SRCDIR+QString("/sounds/pickup3.wav")));
                        m_sPickup->play();
                        break;
                    case 3:
                        m_sPickup = new SoundSource(new SoundFile(SRCDIR+QString("/sounds/pickup4.wav")));
                        m_sPickup->play();
                        break;
                 }
            }
        }
        else
        {
            playItemPickUpFailSound();
        }
}


void cSpieler::scaleObject()
{

    if ( timerForScale.elapsed() > 500 )
    {
        ObjectToMove = getObjectInViewDirection();

         if ( ObjectToMove != nullptr  )
         {

            QMatrix4x4 Scale = QMatrix4x4(2,0,0,0,
                                          0,2,0,0,
                                          0,0,2,0,
                                          0,0,0,1);
            QMatrix4x4 matrixObjekt = ObjectToMove->getEngineModelMatrix();
            matrixObjekt =   Scale * matrixObjekt;
            ObjectToMove->removeFromPhysicEngine();
            ObjectToMove->setGeometryModelMatrix(&matrixObjekt);
            ObjectToMove->addToPhysicEngine();
            //ObjectToMove->getGeometry()->setModelMatrix(matrixObjekt);
            timerForScale.restart();
        }
    }
}

void cSpieler::playFootStepSound()
{
    if ( timerForSounds.elapsed() >  1200 )     //1.2 SEKUNDEN GEHT DIE SOUNDFILE
    {
        m_sFootstep = new SoundSource(new SoundFile(SRCDIR+QString("/sounds/walkingOnGrass.mp3")));
        m_sFootstep->play();
        timerForSounds.restart();
    }
}

void cSpieler::playItemDropSound()
{
    if ( timerForItemDrop.elapsed() >  300 && m_bPickedUp)
    {
        m_sDrop = new SoundSource(new SoundFile(SRCDIR+QString("/sounds/ObjectRelease.wav")));
        m_sDrop->play();
        timerForItemDrop.restart();
    }
}

void cSpieler::playItemPickUpFailSound()
{
    if ( timerForSounds.elapsed() > 400 )
    {
        m_sPickup = new SoundSource(new SoundFile(SRCDIR+QString("/sounds/pickupfail.wav")));
        m_sPickup->play();
        timerForSounds.restart();
    }
}


void cSpieler::isPressed()
{
    if (keyIn->isKeyPressed('e'))
    {
        moveObject();
    }
    else
    {
        playItemDropSound();
        m_bPickedUp = false;
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
        playFootStepSound();
        deltaPosition += mCamera->getViewDir() * mMoveSpeed;
    }
    if (keyIn->isKeyPressed('s'))
    {
        playFootStepSound();
        deltaPosition -= mCamera->getViewDir() * mMoveSpeed;
    }
    if (keyIn->isKeyPressed('a'))
    {
        playFootStepSound();
        deltaPosition -= mCamera->getRightDir() * mMoveSpeed;
    }
    if (keyIn->isKeyPressed('d'))
    {
        playFootStepSound();
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
