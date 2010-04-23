#ifndef ENGINE_H
#define ENGINE_H

// Forward declaration of class UserInterface
class UserInterface;
class View;

#include <string>
#include <sstream>
#include <iostream>
#include <irrlicht.h>

#include "EventHandler.h"
#include "UserInterface.h"
#include "View.h"

#include "extlib/CGUITTFont.h"

using std::cout;
using std::endl;
using std::wstring;
using std::wstringstream;

using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::gui;

enum SceneItemID
{
    SIID_LIGHT      = 1,
    SIID_CAMERA     = 2,
    SIID_MODEL      = 3
};

class Engine
{
    friend class UserInterface;
    friend class View;

private:
    IrrlichtDevice *m_Device;
    IVideoDriver *m_Driver;
    ISceneManager *m_Scene;
    IAnimatedMeshSceneNode *m_LoadedMesh;
    CGUITTFont *m_AxisFont;
    CGUITTFace *m_AxisFontFace;

    dimension2d<u32> *m_WindowSize;

    bool m_RunEngine;

    EventHandler *m_EventHandler;
    UserInterface *m_UserInterface;
    View *m_View;

    void setupScene();
    void drawAxisLines();
    void drawBackground();
    void checkResize();
    IGUIEnvironment *getGUIEnvironment() const;    
    s32 getNumberOfVertices();

public:
    Engine();
    ~Engine();  

    void run(); 
	void loadMesh( const wstring &fileName );
};

#endif // ENGINE_H
