#ifndef VIEW_H
#define VIEW_H

#include <irrlicht.h>

#include "Debug.h"
#include "Engine.h"
#include "Utils.h"

using namespace irr;
using namespace irr::scene;
using namespace irr::core;
using namespace irr::video;

class View : public IEventReceiver
{
private:
    Engine *m_Engine;
    f32 m_Yaw, m_Pitch, m_CameraDistance;
    vector2d<int> *m_LastMousePosition;
    bool m_RotMouse;

    void setNewCameraPosition();
    void setNewLightDirection( const vector3df &cameraPosition );

public:
    View( Engine *engine );
    ~View();

    // IEventReceiver
    virtual bool OnEvent( const SEvent &event );
};

#endif // VIEW_H
