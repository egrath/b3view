#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <iostream>
#include <map>
#include <utility>

#include <irrlicht/irrlicht.h>
#include "Debug.h"

using std::cout;
using std::endl;
using std::map;
using std::make_pair;

enum EventReceiverType
{
    ERT_USERINTERFACE = 1,
    ERT_3DVIEW = 2
};

enum UserEventIdentifier
{
    UEI_WINDOWSIZECHANGED = 1
};

class EventHandler : public irr::IEventReceiver
{
private:
    irr::IrrlichtDevice *m_Device;
    map<EventReceiverType, IEventReceiver*> *m_EventReceivers;
public:
    EventHandler( irr::IrrlichtDevice *device );
    ~EventHandler();

    bool addEventReceiver(EventReceiverType type, irr::IEventReceiver *receiver );

    // IEventReceiver
    virtual bool OnEvent( const irr::SEvent &event );
};

#endif // EVENTHANDLER_H
