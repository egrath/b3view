#include "UserInterface.h"
#include <iostream>

using namespace irr;
using namespace irr::core;
using namespace irr::gui;

using std::string;
using std::wstring;

// PRIVATE
void UserInterface::setupUserInterface()
{
    // Menu
    IGUIContextMenu *menu = m_Gui->addMenu();
    menu->addItem( L"File", UIE_FILEMENU, true, true );
    menu->addItem( L"View", UIE_VIEWMENU, true, true );

    // File Menu
    IGUIContextMenu *fileMenu = menu->getSubMenu( 0 );
    fileMenu->addItem( L"Load", UIC_FILE_LOAD );
    fileMenu->addItem( L"LoadTexture", UIC_FILE_LOAD_TEXTURE );
    fileMenu->addItem( L"Quit", UIC_FILE_QUIT );

    // View Menu
    IGUIContextMenu *viewMenu = menu->getSubMenu( 1 );
    viewMenu->addItem( L"Wireframe Mesh", UIC_VIEW_WIREFRAME, true, false, false, true );
    viewMenu->addItem( L"Lighting",UIC_VIEW_LIGHTING, true, false, true, true );

    // Playback Control Window
    dimension2d<u32> windowSize = m_Engine->m_Driver->getScreenSize();
    IGUIWindow *playbackWindow = m_Gui->addWindow(
            rect<s32>( vector2d<s32>( windowSize.Width - 4 - 160, 28 ), dimension2d<s32>( 160, 300 )), false, L"Playback", nullptr, UIE_PLAYBACKWINDOW );
    playbackWindow->getCloseButton()->setVisible( false );
    s32 spacing_x = 4;
    s32 spacing_y = 4;
    s32 size_x = playbackWindow->getClientRect().getWidth() - 8;
    s32 size_y = 24;
    s32 y = 24;
    playbackStartStopButton = m_Gui->addButton(
            rect<s32>( vector2d<s32>( spacing_x, y ), dimension2d<s32>( size_x, size_y )),
            playbackWindow,
            UIE_PLAYBACKSTARTSTOPBUTTON,
            L"Start/Stop",
            nullptr
    );
    y += size_y + spacing_y;
    playbackIncreaseButton = m_Gui->addButton(
            rect<s32>( vector2d<s32>( spacing_x, y ), dimension2d<s32>( size_x, size_y )),
            playbackWindow,
            UIE_PLAYBACKINCREASEBUTTON,
            L"Faster",
            nullptr
    );
    y += size_y + spacing_y;
    playbackDecreaseButton = m_Gui->addButton(
            rect<s32>( vector2d<s32>( spacing_x, y ), dimension2d<s32>( size_x, size_y )),
            playbackWindow,
            UIE_PLAYBACKDECREASEBUTTON,
            L"Slower",
            nullptr
    );

    // Set Font for UI Elements
    m_GuiFontFace = new CGUITTFace();
    // irrString defines stringc as string<c8>
    std::wstring fontPath = L"ClearSansRegular.ttf";  // core::stringc has implicit conversion to io::path
    // if (QFile(fontPath).exists()) {}
    if (m_GuiFontFace->load(fontPath.c_str())) {  // actually takes `const io::path &`
        m_GuiFont = new CGUITTFont( m_Gui );
        m_GuiFont->attach( m_GuiFontFace, 14 );
        m_Gui->getSkin()->setFont( m_GuiFont );
    }
    else {
        std::wcerr << L"WARNING: Missing '" << fontPath << L"'" << endl;
        delete m_GuiFontFace;
        m_GuiFontFace = nullptr;
        if (m_GuiFont != nullptr) {
            std::wcerr << L"WARNING: Keeping old font loaded." << endl;
        }
    }
    //}
}

void UserInterface::displayLoadFileDialog()
{
    m_Gui->addFileOpenDialog( L"Select file to load", true, nullptr, UIE_LOADFILEDIALOG );
}

void UserInterface::displayLoadTextureDialog()
{
    m_Gui->addFileOpenDialog( L"Select file to load", true, nullptr, UIE_LOADTEXTUREDIALOG );
}

void UserInterface::handleMenuItemPressed( IGUIContextMenu *menu )
{
    s32 id = menu->getItemCommandId( menu->getSelectedItem() );

    switch( id )
    {
    case UIC_FILE_LOAD:
        displayLoadFileDialog();
        break;

    case UIC_FILE_LOAD_TEXTURE:
        displayLoadTextureDialog();
        break;

    case UIC_FILE_QUIT:
        m_Engine->m_RunEngine = false;
        break;

    case UIC_VIEW_WIREFRAME:
        m_WireframeDisplay = m_WireframeDisplay ? false : true;
        m_Engine->setMeshDisplayMode( m_WireframeDisplay, m_Lighting );
        break;

    case UIC_VIEW_LIGHTING:
        m_Lighting = m_Lighting ? false : true;
        m_Engine->setMeshDisplayMode( m_WireframeDisplay, m_Lighting );
        break;
    }
}

// PUBLIC
UserInterface::UserInterface( Engine *engine )
{
    this->playbackStartStopButton = nullptr;
    // For monitoring single press: see
    // <http://irrlicht.sourceforge.net/forum/viewtopic.php?p=210744>
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        keyState[i] = 0;
    LMouseState = 0;
    RMouseState = 0;

    m_Engine = engine;
    m_Gui = engine->getGUIEnvironment();

    m_WireframeDisplay = false;
    m_Lighting = true;

    setupUserInterface();
}

UserInterface::~UserInterface()
{
    delete m_GuiFont;
    delete m_GuiFontFace;
}

IGUIEnvironment * UserInterface::getGUIEnvironment() const
{
    return m_Gui;
}

void UserInterface::drawStatusLine() const
{
}

// IEventReceiver
bool UserInterface::OnEvent( const SEvent &event )
{
    // Events arriving here should be destined for us
    if (event.EventType == EET_KEY_INPUT_EVENT) {
        if (event.KeyInput.PressedDown && !KeyIsDown[event.KeyInput.Key]) {
            if (event.KeyInput.Key == irr::KEY_KEY_T) {
                this->m_Engine->m_NextPath = L"";
                std::wstring basePath = L".";
                if (this->m_Engine->m_PreviousPath.length() > 0) {
                    // std::wcerr << "this->m_PreviousPath: " <<  this->m_PreviousPath.c_str() << endl;
                    std::wstring lastName = Utility::basename(this->m_Engine->m_PreviousPath);
                    std::wstring lastDirPath = Utility::parentOfPath(this->m_Engine->m_PreviousPath);
                    // std::wcerr << "lastDirPath: " <<  lastDirPath << endl;
                    std::wstring parentPath = Utility::parentOfPath(lastDirPath);
                    // std::wcerr << "parentPath: " <<  parentPath << endl;
                    std::wstring dirSeparator = Utility::delimiter(this->m_Engine->m_PreviousPath);
                    std::wstring texturesPath = parentPath + dirSeparator + L"textures";
                    // std::wcerr << "lastName: " <<  lastName << endl;
                    // std::wcerr << "pathWithoutExt: " <<  Utility::withoutExtension(m_PreviousPath) << endl;
                    // std::wcerr << "nameWithoutExt: " <<  Utility::withoutExtension(lastName) << endl;
                    std::wstring tryTexPath = texturesPath + dirSeparator + Utility::withoutExtension(lastName) + L".png";
                    if (Utility::exists(tryTexPath)) {
                        this->m_Engine->m_NextPath = tryTexPath;
                        this->m_Engine->loadTexture(this->m_Engine->m_NextPath);
                    }
                }
                else debug() <<  "Can't cycle texture since no file was opened" << endl;
            }
            else if (event.KeyInput.Char == L'+' || event.KeyInput.Char == L'=') {
                m_Engine->setAnimationFPS(m_Engine->animationFPS() + 5);
                // std::wcerr << "m_Engine->animationFPS(): " << m_Engine->animationFPS() << endl;
            }
            else if (event.KeyInput.Char == L'-') {
                if (m_Engine->animationFPS() > 0) {
                    m_Engine->setAnimationFPS(m_Engine->animationFPS() - 5);
                }
                // std::wcerr << "m_Engine->animationFPS(): " << m_Engine->animationFPS() << endl;
            }
            else if (event.KeyInput.Char == L' ') {
                m_Engine->toggleAnimation();
                // std::wcerr << "m_Engine->animationFPS(): " << m_Engine->animationFPS() << endl;
            }
            // std::wcerr << "Char: " << event.KeyInput.Char << endl;
        }
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        return true;
    }
    else if (event.EventType == EET_MOUSE_INPUT_EVENT)
    {
       switch ( event.MouseInput.Event)
       {
          case EMIE_LMOUSE_LEFT_UP:
             if ( LMouseState == 2)
             {
                LMouseState = 3;
             }
          break;
          case EMIE_LMOUSE_PRESSED_DOWN:
             if ( LMouseState == 0)
             {
                LMouseState = 1;
             }
          break;
          case EMIE_RMOUSE_LEFT_UP:
             if ( RMouseState  == 2)
             {
                RMouseState = 3;
             }
          break;
          case EMIE_RMOUSE_PRESSED_DOWN:
             if ( RMouseState == 0)
             {
                RMouseState = 1;
             }
          break;
       }
    }
    else if (!(event.EventType == EET_GUI_EVENT))
        return false;

    const SEvent::SGUIEvent *ge = &( event.GUIEvent );

    bool isPress = false;



    switch( ge->Caller->getID() )
    {
    case UIE_FILEMENU:
    case UIE_VIEWMENU:
        // call handler for all menu related actions
        handleMenuItemPressed( static_cast<IGUIContextMenu *>( ge->Caller ));
        break;    

    case UIE_LOADFILEDIALOG:
        if( ge->EventType == EGET_FILE_SELECTED )
        {
            IGUIFileOpenDialog *fileOpenDialog = static_cast<IGUIFileOpenDialog *>( ge->Caller );
            m_Engine->loadMesh( fileOpenDialog->getFileName() );
        }
        break;

    case UIE_LOADTEXTUREDIALOG:
        if( ge->EventType == EGET_FILE_SELECTED )
        {
            IGUIFileOpenDialog *fileOpenDialog = static_cast<IGUIFileOpenDialog *>( ge->Caller );
            m_Engine->loadTexture( fileOpenDialog->getFileName() );
        }
        break;

    case UIE_PLAYBACKSTARTSTOPBUTTON:
        if ( ge->EventType == EGET_BUTTON_CLICKED) {
            this->m_Engine->toggleAnimation();
        }
        break;

    case UIE_PLAYBACKINCREASEBUTTON:
        if ( ge->EventType == EGET_BUTTON_CLICKED) {
            this->m_Engine->setAnimationFPS(this->m_Engine->animationFPS() + 5);
        }
        break;

    case UIE_PLAYBACKDECREASEBUTTON:
        if ( ge->EventType == EGET_BUTTON_CLICKED) {
            if (this->m_Engine->animationFPS() >= 5) {
                this->m_Engine->setAnimationFPS(this->m_Engine->animationFPS() - 5);
            }
        }
        break;

    default:
        break;
    }

    return true;
}
