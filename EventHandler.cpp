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
        map<EventReceiverType,IEventReceiver *>::iterator iter = m_EventReceivers->find( ERT_USERINTERFACE );
        iter->second->OnEvent( event );
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
