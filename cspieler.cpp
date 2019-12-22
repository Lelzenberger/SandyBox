#include "cspieler.h"
#include "inputregistry.h"
#include "openglwidget.h"
#include "scenemanager.h"
#include "simplesphere.h"
#include "color.h"


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

void cSpieler::createCrosshair()
{
    if ( ! m_bCrosshairFirst )
    {
        m_dCrosshair = new Drawable(new SimpleSphere(1));
        m_dCrosshair->getProperty<Color>()->setValue(1.0,0.0,0.0,1.0f);
        m_rootNode->addChild(new Node(m_dCrosshair));
        m_bCrosshairFirst = true;
    }

    QVector3D camPos = m_cam->getPosition();
    QVector3D lookDirection = m_cam->getViewDir();
    QMatrix4x4 crossHairMatrix = m_dCrosshair->getWorldMatrix();
    QMatrix4x4 old = m_dCrosshair->getWorldMatrix();


    crossHairMatrix.setColumn(3, (camPos + 5 * lookDirection).toVector4D());
//ER SETZTE DIE WERTE NICH?!? BERECHNET WERDEN SIE ABER!
    m_dCrosshair->setModelMatrix(crossHairMatrix);
// ----------------
    if (keyIn->isKeyPressed('r'))
    {
        qDebug("OLD: %i", old.column(3));
        qDebug("NEW: %i", crossHairMatrix.column(3));
    }
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
                playPickOrDrop(false);
            }
        }
}

void cSpieler::playPickOrDrop(bool DropSound)
{
    if (!DropSound)
    {
        int i = timerForScale.elapsed() % 4 ;
        switch(i)
        {

            case 0:

                file = new SoundSource(new SoundFile(SRCDIR+QString("/sounds/pickup1.wav")));
                file->play();
                break;

            case 1:

                file = new SoundSource(new SoundFile(SRCDIR+QString("/sounds/pickup2.wav")));
                file->play();
                break;

            case 2:
                file = new SoundSource(new SoundFile(SRCDIR+QString("/sounds/pickup3.wav")));
                file->play();
                break;
            case 3:
                file = new SoundSource(new SoundFile(SRCDIR+QString("/sounds/pickup4.wav")));
                file->play();
                break;
         }
    }
    else if (DropSound)
    {

        file = new SoundSource(new SoundFile(SRCDIR+QString("/sounds/drop.wav")));
        file->play();
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
        }
    }
}


void cSpieler::isPressed()
{
    if (keyIn->isKeyPressed('e'))
        {
            moveObject();
            timerForSound.restart();
        }
        else
    {
            m_bPickedUp = false;
            if ( timerForSound.elapsed() > 50 && timerForSound.elapsed() < 100)
            {
                playPickOrDrop(true);
            }


    }

    if (keyIn->isKeyPressed('q'))
        {
            scaleObject();
        }
}


void cSpieler::controlCamera()
{

//Crosshair aus
    if (/*m_rootNode*/ false)
    {
         createCrosshair();
    }
   // else         qDebug("SetRoot Node in cSpieler!");

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

void cSpieler::setRoot(Node * root)
{
    m_rootNode = root;
}


void cSpieler::setPhysicEngine(PhysicEngine *PhysicEngine)
{
    m_PhysicEngine = PhysicEngine;
}

Camera *cSpieler::getCamera()
{
    return m_cam;
}
