#ifndef USERINTERFACE_H
#define USERINTERFACE_H

// Forward declaration of class Engine
class Engine;

#include <sstream>
#include <string>
#include <irrlicht/irrlicht.h>

#include "Debug.h"
#include "Engine.h"

#include "extlib/CGUITTFont.h"

using namespace irr;
using namespace irr::core;
using namespace irr::gui;

using std::string;
using std::wstring;

enum UserInterfaceElements
{
    UIE_PLAYBACKWINDOW              = 1000,
    UIE_LOADBUTTON                  = 1001,
    UIE_LOADFILEDIALOG              = 1002,
    UIE_FILEMENU                    = 1003,
    UIE_PLAYBACKSTARTSTOPBUTTON     = 1004,
    UIE_VIEWMENU                    = 1005,
    UIE_LOADTEXTUREDIALOG           = 1006
};

enum UserInterfaceCommands
{
    UIC_FILE_LOAD           = 1000,
    UIC_FILE_QUIT           = 1001,
    UIC_FILE_LOAD_TEXTURE   = 1002,
    UIC_VIEW_WIREFRAME      = 2000,
    UIC_VIEW_LIGHTING       = 2001
};

class UserInterface : public IEventReceiver
{
private:
    Engine *m_Engine;
    IGUIEnvironment *m_Gui;
    CGUITTFont *m_GuiFont;
    CGUITTFace *m_GuiFontFace;

    void setupUserInterface();
    void displayLoadFileDialog();
    void displayLoadTextureDialog();
    void handleMenuItemPressed( IGUIContextMenu *menu );

    bool m_WireframeDisplay;
    bool m_Lighting;

public:
    UserInterface( Engine *device );
    ~UserInterface();
    IGUIEnvironment * getGUIEnvironment() const;
    void drawStatusLine() const;

    // IEventReceiver
    virtual bool OnEvent( const SEvent &event );
};

#endif // USERINTERFACE_H
