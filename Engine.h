#ifndef ENGINE_H
#define ENGINE_H

// Forward declaration of class UserInterface
class UserInterface;
class View;

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include <irrlicht/irrlicht.h>
#include "EventHandler.h"
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
    std::wstring m_NextPath;
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
    bool isPlaying;
    irr::u32 worldFPS;
    irr::u32 prevFPS;
    std::vector<std::wstring> textureExtensions;
    // Making materials in contructor or setupScene causes segfault at
    // `m_Driver->setMaterial( *lineX );` in
    // `Engine::drawAxisLines` for unknown reason:
//    irr::video::SMaterial *lineX;
//    irr::video::SMaterial *lineY;
//    irr::video::SMaterial *lineZ;
    irr::core::vector3df m_CamPos;
    irr::core::vector3df m_CamTarget;
    std::wstring m_FontPath = L"ClearSansRegular.ttf";  // core::stringc has implicit conversion to io::path
    bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    irr::s32 keyState[irr::KEY_KEY_CODES_COUNT];
    irr::s32 LMouseState,RMouseState;

public:
    std::wstring m_PreviousPath;
    std::wstring m_PrevTexturePath;


    Engine();
    ~Engine();  

    void run();
    void loadMesh( const std::wstring &fileName );
    void reloadMesh();
    void reloadTexture();
    bool loadTexture( const std::wstring &fileName );
    void setMeshDisplayMode( bool wireframe = false, bool lighting = true );
    bool isAnimating();
    void playAnimation();
    void pauseAnimation();
    void toggleAnimation();
    void setAnimationFPS(irr::u32 animationFPS);
    void setZUp(bool zUp);
    irr::u32 animationFPS();
};

#endif // ENGINE_H
