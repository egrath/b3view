#include "View.h"
#include "Engine.h"

using namespace irr;
using namespace irr::core;
using namespace irr::scene;

void View::setNewCameraPosition()
{
    vector3d<f32> newCameraPosition;
    ICameraSceneNode *camera = m_Engine->m_Scene->getActiveCamera();
    vector3df oldCamPos = camera->getPosition();
    // vector3df oldCamRot = camera->getRotation();
    // NOTE: rotationToDirection converts a rotation to a vec3 direction.
    // vector3df oldCamRot = m_Engine->tmpPosVec3f.?(m_Engine->tmpTargetVec3f);
    newCameraPosition.X = 0;
    newCameraPosition.Y = m_CameraDistance * sin( m_Pitch );
    newCameraPosition.Z = m_CameraDistance * cos( m_Pitch );

    matrix4 yawMatrix;
    yawMatrix.setRotationRadians( vector3df( 0, m_Yaw, 0 ));
    yawMatrix.transformVect( newCameraPosition );

    newCameraPosition.Y = oldCamPos.Y;
    camera->setPosition( newCameraPosition );
    // vector3df newRotation();
    // camera->setRotation();
    // camera->setTarget(m_Engine->tmpTargetVec3f);

    // Set Light direction
    setNewLightDirection( newCameraPosition );
}

void View::setNewLightDirection( const vector3df &cameraPosition )
{
    ILightSceneNode *light = static_cast<ILightSceneNode *>( m_Engine->m_Scene->getSceneNodeFromId( SIID_LIGHT ));

    matrix4 m;
    m.buildRotateFromTo( vector3df( 0, 0, 1 ), vector3df( cameraPosition ).invert().normalize() );

    light->setRotation( m.getRotationDegrees() );
}

View::View( Engine *engine )
{
    m_Engine = engine;
    m_LastMousePosition = new vector2d<int>();
    m_RotMouse = false;

    m_Pitch = PI;

    // Set Camera Distance
    m_CameraDistance = 10;

    // vectors for angle are opposite, since camera revolves around center
    vector3df offsetVec3(
        engine->m_CamPos.X-engine->m_CamTarget.X,
        engine->m_CamPos.Y-engine->m_CamTarget.Y,
        engine->m_CamPos.Z-engine->m_CamTarget.Z
    );
    // m_CameraDistance = sqrtf()
    m_CameraDistance = offsetVec3.getLength();
    // NOTE: rotationToDirection converts a rotation to a vec3 direction
    // vector3df rotationVec3 = engine->tmpPosVec3f.?(engine->tmpTargetVec3f);
    // vector3df rotationVec3 = engine->tmpTargetVec3f.?(engine->tmpPosVec3f);

    // see rogerborg on <http://irrlicht.sourceforge.net/forum/viewtopic.php?f=1&t=30477>
    // const f32 dot = engine->tmpTargetVec3f.dotProduct(engine->tmpPosVec3f); // to...(from) // angle only

    m_Yaw = atan2(offsetVec3.X, offsetVec3.Z);
    m_Pitch = asin(-offsetVec3.Y);

    // m_Yaw = rotationVec3.Y;
    // m_Pitch = rotationVec3.X;

    debug() << "Yaw: " << radToDeg(m_Yaw) << endl;
    debug() << "Pitch: " << radToDeg(m_Pitch) << endl;
}

View::~View()
{
    delete m_LastMousePosition;
}

// IEventReceiver
bool View::OnEvent( const SEvent &event )
{
    // If it's not a mouse event or window resize event, return
    if( event.EventType != EET_MOUSE_INPUT_EVENT && !( event.EventType == EET_USER_EVENT && event.UserEvent.UserData1 == UEI_WINDOWSIZECHANGED ))
        return false;

    // Handle window resize
    if( event.EventType == EET_USER_EVENT && event.UserEvent.UserData1 == UEI_WINDOWSIZECHANGED )
    {
        dimension2d<u32> windowSize = m_Engine->m_Driver->getScreenSize();
        f32 aspectRatio = (f32) windowSize.Width / windowSize.Height;
        debug() << "Setting aspect to: " << aspectRatio << endl;
        m_Engine->m_Scene->getActiveCamera()->setAspectRatio( aspectRatio );
    }

    // Handle mouse event
    const SEvent::SMouseInput *mouseEvent = &( event.MouseInput );

    if( mouseEvent->Event == EMIE_MMOUSE_PRESSED_DOWN )
    {
        m_RotMouse = true;
        m_LastMousePosition->X = mouseEvent->X;
        m_LastMousePosition->Y = mouseEvent->Y;
    }
    else if( mouseEvent->Event == EMIE_MMOUSE_LEFT_UP )
    {
        m_RotMouse = false;
    }
    else if( mouseEvent->Event == EMIE_MOUSE_WHEEL )
    {
        f32 distanceDelta = mouseEvent->Wheel / 2.5f;
        if( m_CameraDistance - distanceDelta > 0.1f )
            m_CameraDistance -= distanceDelta;

        setNewCameraPosition();
    }
    else if( m_RotMouse )
    {
        int dx = mouseEvent->X - m_LastMousePosition->X;
        int dy = mouseEvent->Y - m_LastMousePosition->Y;

        m_LastMousePosition->X = mouseEvent->X;
        m_LastMousePosition->Y = mouseEvent->Y;

        f32 pitchDelta = dy / 120.0f;
        if(( m_Pitch - pitchDelta > ( PI - ( PI / 2 ))) && ( m_Pitch - pitchDelta < PI + ( PI/2 )))
            m_Pitch -= dy / 120.0f;

        m_Yaw += dx / 120.0f;

        // Set Camera to new rotation
        setNewCameraPosition();
    }

    return true;
}
