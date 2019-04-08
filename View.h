#ifndef VIEW_H
#define VIEW_H

#include <irrlicht/irrlicht.h>

class Engine;

class View : public irr::IEventReceiver
{
private:
    Engine *m_Engine;
    irr::f32 m_Yaw, m_Pitch, m_CameraDistance;
    irr::core::vector2d<int> *m_LastMousePosition;
    bool m_RotMouse;
    bool m_zUp;

    void setNewCameraPosition();
    void setNewCameraPosition(bool zUp);
    void setNewLightDirection( const irr::core::vector3df &cameraPosition );

public:
    View( Engine *engine );
    ~View();
    void setZUp(bool zUp);
    void setCameraDistance(float cameraDistance);
    bool zUp();
    bool m_Shift;

    // IEventReceiver
    virtual bool OnEvent( const irr::SEvent &event );
};

#endif  // VIEW_H
