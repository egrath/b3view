#ifndef ENGINE_H
#define ENGINE_H

// Forward declaration of class UserInterface
class UserInterface;
class View;

#include <string>
#include <sstream>
#include <iostream>
#include <irrlicht/irrlicht.h>

#include "EventHandler.h"
#include "UserInterface.h"
#include "View.h"

#include "extlib/CGUITTFont.h"

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
    irr::IrrlichtDevice *m_Device;
    irr::video::IVideoDriver *m_Driver;
    irr::scene::ISceneManager *m_Scene;
    irr::scene::IAnimatedMeshSceneNode *m_LoadedMesh;
    irr::scene::ILightSceneNode *m_SceneLight;
    irr::gui::CGUITTFont *m_AxisFont;
    irr::gui::CGUITTFace *m_AxisFontFace;

    irr::core::dimension2d<irr::u32> *m_WindowSize;

    bool m_RunEngine;

    EventHandler *m_EventHandler;
    UserInterface *m_UserInterface;
    View *m_View;

    void setupScene();
    void drawAxisLines();
    void drawBackground();
    void checkResize();
    irr::gui::IGUIEnvironment *getGUIEnvironment() const;
    irr::s32 getNumberOfVertices();

public:
    Engine();
    ~Engine();  

    void run();
    void loadMesh( const std::wstring &fileName );
    void reloadMesh();
    void loadTexture( const std::wstring &fileName );
    void setMeshDisplayMode( bool wireframe = false, bool lighting = true );
};

#endif // ENGINE_H
