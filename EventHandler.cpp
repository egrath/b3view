#include "EventHandler.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <Utils.h>

using namespace irr;
using namespace irr::video;
using namespace irr::gui;

// Public
EventHandler::EventHandler( IrrlichtDevice *device )
{
    // For monitoring single press: see
    // <http://irrlicht.sourceforge.net/forum/viewtopic.php?p=210744>
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        keyState[i] = 0;
    LMouseState = 0;
    RMouseState = 0;
    m_Device = device;
    m_EventReceivers = new map<EventReceiverType, IEventReceiver *>();
}

EventHandler::~EventHandler()
{
    delete m_EventReceivers;
}

bool EventHandler::addEventReceiver( EventReceiverType type, IEventReceiver *receiver )
{
    m_EventReceivers->insert( make_pair( type, receiver ));
    return true;
}

// IEventReceiver
bool EventHandler::OnEvent( const SEvent &event )
{
    if (event.EventType == EET_GUI_EVENT)
    {
        // Pass to User Interface Handler
        map<EventReceiverType,IEventReceiver *>::iterator iter = m_EventReceivers->find( ERT_USERINTERFACE );
        iter->second->OnEvent( event );
    }
    else if (event.EventType == EET_MOUSE_INPUT_EVENT)
    {
        map<EventReceiverType,IEventReceiver *>::iterator iter = m_EventReceivers->find( ERT_3DVIEW );
        iter->second->OnEvent( event );
    }
    else if (event.EventType == EET_KEY_INPUT_EVENT) {
        if (event.KeyInput.PressedDown && !KeyIsDown[event.KeyInput.Key]) {
            std::wstring basePath = L".";
            if (this->m_PreviousPath.length() > 0) {
                // std::wcerr << "this->m_PreviousPath: " <<  this->m_PreviousPath.c_str() << endl;
                std::wstring lastDirPath = Utility::parentOfPath(m_PreviousPath);
                std::wcerr << "lastDirPath: " <<  lastDirPath << endl;
            }
            else debug() <<  "Keydown" << endl;
        }
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
    else if (event.EventType == EET_USER_EVENT)
    {
        if (event.UserEvent.UserData1 == UEI_WINDOWSIZECHANGED) {
            // Window resize handling - send to all subscribers
            map<EventReceiverType,IEventReceiver *>::iterator iter;
            for( iter = m_EventReceivers->begin(); iter != m_EventReceivers->end(); iter ++ )
                iter->second->OnEvent( event );
        }
    }

    return false;
}
