#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <iostream>
#include <map>
#include <utility>

#include <irrlicht.h>

#include "Debug.h"

using std::cout;
using std::endl;
using std::map;
using std::make_pair;

using namespace irr;
using namespace irr::video;
using namespace irr::gui;

enum EventReceiverType
{
    ERT_USERINTERFACE = 1,
    ERT_3DVIEW = 2
};

enum UserEventIdentifier
{
    UEI_WINDOWSIZECHANGED = 1
};

class EventHandler : public IEventReceiver
{
private:
    IrrlichtDevice *m_Device;
    map<EventReceiverType, IEventReceiver*> *m_EventReceivers;

public:
    EventHandler( IrrlichtDevice *device );
    ~EventHandler();

    bool addEventReceiver( EventReceiverType type, IEventReceiver *receiver );

    // IEventReceiver
    virtual bool OnEvent( const SEvent &event );
};

#endif // EVENTHANDLER_H
