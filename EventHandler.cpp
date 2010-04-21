#include "EventHandler.h"

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
}

// IEventReceiver
bool EventHandler::OnEvent( const SEvent &event )
{
    if( event.EventType == EET_GUI_EVENT )
    {
        // Pass to User Interface Handler
        map<EventReceiverType,IEventReceiver *>::iterator iter = m_EventReceivers->find( ERT_USERINTERFACE );
        iter->second->OnEvent( event );
    }
    else if( event.EventType == EET_MOUSE_INPUT_EVENT )
    {
        map<EventReceiverType,IEventReceiver *>::iterator iter = m_EventReceivers->find( ERT_3DVIEW );
        iter->second->OnEvent( event );
    }

    return false;
}
