#include "UserInterface.h"

// PRIVATE
void UserInterface::setupUserInterface()
{
    IGUIContextMenu *menu = m_Gui->addMenu();
    menu->addItem( L"File", UIE_FILEMENU, true, true );

    IGUIContextMenu *fileMenu = menu->getSubMenu( 0 );
    fileMenu->addItem( L"Load", UIC_FILE_LOAD );
    fileMenu->addItem( L"Quit", UIC_FILE_QUIT );


    // Set Font for UI Elements
    m_GuiFont = m_Gui->getFont( "arial.xml" );
    m_Gui->getSkin()->setFont( m_GuiFont );
}

void UserInterface::displayLoadFileDialog()
{
    m_Gui->addFileOpenDialog( L"Select file to load", true, 0, UIE_LOADFILEDIALOG );
}

// PUBLIC
UserInterface::UserInterface( Engine *engine )
{
    m_Engine = engine;
    m_Gui = engine->getGUIEnvironment();

    setupUserInterface();
}

UserInterface::~UserInterface()
{
    delete m_GuiFont;
}

IGUIEnvironment * UserInterface::getGUIEnvironment() const
{
    return m_Gui;
}

void UserInterface::handleMenuItemPressed( IGUIContextMenu *menu )
{
    s32 id = menu->getItemCommandId( menu->getSelectedItem() );

    switch( id )
    {
    case UIC_FILE_LOAD:
        displayLoadFileDialog();
        break;

    case UIC_FILE_QUIT:
        m_Engine->m_RunEngine = false;
        break;
    }
}

// IEventReceiver
bool UserInterface::OnEvent( const SEvent &event )
{
    // Events arriving here should be destined for us
    if( ! event.EventType == EET_GUI_EVENT )
        return false;

    const SEvent::SGUIEvent *ge = &( event.GUIEvent );

    switch( ge->Caller->getID() )
    {
    case UIE_FILEMENU:
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

    default:
        break;
    }

    return true;
}
