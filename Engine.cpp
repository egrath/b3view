#include "Engine.h"

using std::cout;
using std::endl;
using std::wstring;
using std::wstringstream;

using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace irr::gui;

/* //////////////////////////////////////////////////////////////////////////
   PRIVATE METHODS
   /////////////////////////////////////////////////////////////////////// */

void Engine::setupScene()
{
    // Setup Light
    m_SceneLight = m_Scene->addLightSceneNode();
    m_SceneLight->setID( SIID_LIGHT );
    m_SceneLight->setLightType( ELT_DIRECTIONAL );
    m_SceneLight->getLightData().AmbientColor = SColorf( 0.2f, 0.2f, 0.2f );
    m_SceneLight->getLightData().DiffuseColor = SColorf( 0.8f, 0.8f, 0.8f );
    m_Scene->setAmbientLight( SColorf( 0.2f, 0.2f, 0.2f ));

    // Setup Camera
    ICameraSceneNode *camera = m_Scene->addCameraSceneNode( nullptr, vector3df( 0, 0, -10 ), vector3df() );
    camera->setAspectRatio(( f32 ) m_Driver->getScreenSize().Width / m_Driver->getScreenSize().Height );
}

IGUIEnvironment * Engine::getGUIEnvironment() const
{
    return m_Device->getGUIEnvironment();
}

void Engine::drawAxisLines()
{
    SMaterial *lineX = new SMaterial();
    lineX->Lighting = false;
    lineX->EmissiveColor = SColor( 255, 255, 0, 0 );
    lineX->Thickness = 1.0f;

    SMaterial *lineY = new SMaterial( *lineX );
    lineY->EmissiveColor = SColor( 255, 0, 255, 0 );

    SMaterial *lineZ = new SMaterial( *lineX );
    lineZ->EmissiveColor = SColor( 255, 0, 0, 255 );

    m_Driver->setTransform( ETS_WORLD, matrix4() );

    m_Driver->setMaterial( *lineX );
    m_Driver->draw3DLine( vector3df(), vector3df( 5, 0, 0 ), SColor( 255, 255, 0, 0 ));
    position2d<s32> textPos = m_Scene->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition( vector3df( 5.2, 0, 0 ));
    dimension2d<u32> textSize;
    if (m_AxisFont != nullptr) {
        textSize = m_AxisFont->getDimension( L"X+" );
        m_AxisFont->draw( L"X+", rect<s32>( textPos, textSize ), SColor( 255, 255, 0, 0 ), true, true );
    }
    m_Driver->setMaterial( *lineY );
    m_Driver->draw3DLine( vector3df(), vector3df( 0, 5, 0 ), SColor( 255, 0, 255, 0 ));
    textPos = m_Scene->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition( vector3df( 0, 5.2, 0 ));
    if (m_AxisFont != nullptr) {
        textSize = m_AxisFont->getDimension( L"Y+" );
        m_AxisFont->draw( L"Y+", rect<s32>( textPos, textSize ), SColor( 255, 0, 255, 0 ), true, true );
    }
    m_Driver->setMaterial( *lineZ );
    m_Driver->draw3DLine( vector3df(), vector3df( 0, 0, 5 ), SColor( 255, 0, 0, 255 ));
    textPos = m_Scene->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition( vector3df( 0, 0, 5.2 ));
    if (m_AxisFont != nullptr) {
        textSize = m_AxisFont->getDimension( L"Z+" );
        m_AxisFont->draw( L"Z+", rect<s32>( textPos, textSize ), SColor( 255, 0, 0, 255 ), true, true );
    }
    delete lineX;
    delete lineY;
    delete lineZ;
}

void Engine::drawBackground()
{
    dimension2d<u32> screenSize = m_Driver->getScreenSize();
    m_Driver->draw2DRectangle( rect<s32>( 0, 0, screenSize.Width, screenSize.Height ),
        SColor( 255, 128, 128, 255 ),
        SColor( 255, 128, 128, 255 ),
        SColor( 255, 224, 224, 255 ),
        SColor( 255, 224, 224, 255 ));
}

void Engine::checkResize()
{
    if(( m_WindowSize->Width != m_Driver->getScreenSize().Width ) || ( m_WindowSize->Height != m_Driver->getScreenSize().Height ))
    {
        m_WindowSize->Width = m_Driver->getScreenSize().Width;
        m_WindowSize->Height = m_Driver->getScreenSize().Height;

        // Send custom event
        IEventReceiver *eventReceiver = m_Device->getEventReceiver();

        SEvent event;
        event.EventType = EET_USER_EVENT;
        event.UserEvent.UserData1 = UEI_WINDOWSIZECHANGED;

        eventReceiver->OnEvent( event );
    }
}

s32 Engine::getNumberOfVertices()
{
    IMesh *mesh = m_LoadedMesh->getMesh()->getMesh( 0, 255, -1, -1 );

    int vertices = 0;
    for( int bufferIndex = 0; bufferIndex < mesh->getMeshBufferCount(); bufferIndex ++ )
        vertices += mesh->getMeshBuffer( bufferIndex )->getVertexCount();

    cout << vertices << endl;

    return vertices;
}

/* //////////////////////////////////////////////////////////////////////////
   PUBLIC METHODS
   /////////////////////////////////////////////////////////////////////// */

Engine::Engine()
{
    this->worldFPS = 60;
    this->prevFPS = 30;
#if WIN32
    m_Device = createDevice( EDT_DIRECT3D9, dimension2d<u32>( 1024, 768 ), 32, false, false, false, nullptr );
#else
    m_Device = createDevice( EDT_OPENGL, dimension2d<u32>( 1024, 768 ), 32, false, false, false, nullptr );
#endif
    m_Device->setResizable( true );

    m_EventHandler = new EventHandler( m_Device );
    m_Device->setEventReceiver( m_EventHandler );

    m_Driver = m_Device->getVideoDriver();
    m_Scene = m_Device->getSceneManager();

    wstringstream windowTitle;
    windowTitle << L"b3view (Blitz3D/Irrlicht Viewer) [" << m_Driver->getName() << L"]";
    m_Device->setWindowCaption( windowTitle.str().c_str() );

    setupScene();

    // Setup User Interface
    m_UserInterface = new UserInterface( this );
    m_EventHandler->addEventReceiver( ERT_USERINTERFACE, m_UserInterface );

    // Setup 3D View
    m_View = new View( this );
    m_EventHandler->addEventReceiver( ERT_3DVIEW, m_View );

    // Load font for displaying Axis names
    m_AxisFontFace = new CGUITTFace();
    if (m_AxisFontFace->load( "ClearSansRegular.ttf" )) {
        m_AxisFont = new CGUITTFont( m_UserInterface->getGUIEnvironment() );
        m_AxisFont->attach( m_AxisFontFace, 14 );
        m_AxisFont->AntiAlias = false;
    }
    else {
        delete m_AxisFontFace;
        m_AxisFontFace = nullptr;
    }
    // Set Engine enabled
    m_RunEngine = true;
    m_LoadedMesh = nullptr;

    // Store actual window size
    m_WindowSize = new dimension2d<u32>();
    m_WindowSize->Width = m_Driver->getScreenSize().Width;
    m_WindowSize->Height = m_Driver->getScreenSize().Height;
    this->playAnimation();
}

Engine::~Engine()
{
    m_Device->drop();
    delete m_WindowSize;
    delete m_AxisFont;
    delete m_AxisFontFace;
}

void Engine::loadMesh( const wstring &fileName )
{
    // if (m_LoadedMesh != nullptr) {
    //std::wstring fn;
    //fn.assign(fileName.c_str());
    // std::wcerr << "fileName = " << fn << endl;
    // std::wcerr << "fileName = " << fileName << endl;
    this->m_PreviousPath = fileName;
    // std::wcerr << "this->m_PreviousPath = " << this->m_PreviousPath.c_str() << endl;
    // }
    if( m_LoadedMesh != nullptr )
        m_LoadedMesh->remove();

    m_LoadedMesh = m_Scene->addAnimatedMeshSceneNode( m_Scene->getMesh( fileName.c_str()));
    Utility::dumpMeshInfoToConsole( m_LoadedMesh );
}

void Engine::reloadMesh()
{
    if (this->m_PreviousPath.length() > 0) {
        std::wcerr << "this->m_PreviousPath = " << this->m_PreviousPath.c_str() << endl;
        loadMesh(this->m_PreviousPath);
    }
}

bool Engine::loadTexture(const wstring &fileName)
{
    ITexture* texture = this->m_Driver->getTexture(fileName.c_str());
    bool ret = false;
    if (texture != nullptr) {
        m_LoadedMesh->setMaterialTexture(0, texture);
        ret = true;
    }
    this->m_PrevTexturePath = fileName;
    return ret;
}

void Engine::setMeshDisplayMode( bool wireframe, bool lighting )
{
    for( int materialIndex = 0; materialIndex < m_LoadedMesh->getMaterialCount(); materialIndex ++ )
    {
        // Set Wireframe display
        m_LoadedMesh->getMaterial( materialIndex ).Wireframe = wireframe;

        // Set Lighting
        if( ! lighting )
        {
            m_LoadedMesh->getMaterial( materialIndex ).Lighting = false;
            m_LoadedMesh->getMaterial( materialIndex ).EmissiveColor = SColor( 255, 255, 255, 255 );
        }
        else
        {
            m_LoadedMesh->getMaterial( materialIndex ).Lighting = true;
            m_LoadedMesh->getMaterial( materialIndex ).EmissiveColor = SColor( 255, 0, 0, 0 );
        }
    }
}

bool Engine::isAnimating()
{
    return this->isPlaying;
}

void Engine::playAnimation()
{
    if (this->animationFPS() < 1) {
        this->setAnimationFPS(5);
    }
    if (!this->isAnimating()) {
        if (this->m_LoadedMesh != nullptr) {
            if (this->prevFPS < 1) this->prevFPS = 5;
            this->m_LoadedMesh->setAnimationSpeed(this->prevFPS);
        }
    }
    this->isPlaying = true;
}

void Engine::pauseAnimation()
{
    if (this->isAnimating()) {
        this->prevFPS = animationFPS();
        if (this->m_LoadedMesh != nullptr) {
            this->prevFPS = this->m_LoadedMesh->getAnimationSpeed();
            this->m_LoadedMesh->setAnimationSpeed(0);
        }
    }
    this->isPlaying = false;
}

void Engine::toggleAnimation()
{
    if (this->isAnimating()) {
        this->pauseAnimation();
        debug() << "paused " << this->animationFPS() << "fps" << endl;
    }
    else {
        this->playAnimation();
        debug() << "unpaused " << this->animationFPS() << "fps" << endl;
    }

}

void Engine::setAnimationFPS(u32 animationFPS)
{
    if (this->m_LoadedMesh != nullptr) {
        this->m_LoadedMesh->setAnimationSpeed(animationFPS);
    }
}

u32 Engine::animationFPS()
{
    u32 ret = 0;
    if (this->m_LoadedMesh != nullptr) {
        ret = this->m_LoadedMesh->getAnimationSpeed();
    }
    return ret;
}

void Engine::run()
{
    u32 timePerFrame = 1000.0f;
    if (this->worldFPS > 0) {
        timePerFrame = ( u32 ) ( 1000.0f / this->worldFPS );
    }
    ITimer *timer = m_Device->getTimer();       

    // Run the Device with fps frames/sec
    while( m_Device->run() && m_RunEngine )
    {
        u32 startTime = timer->getRealTime();

        checkResize();
        if (this->m_LoadedMesh != nullptr) {
            //this->m_LoadedMesh->setAnimationSpeed(this->fps);
            if (isPlaying) {
                this->m_LoadedMesh->setLoopMode(true);
            }
            else {
                this->m_LoadedMesh->setLoopMode(false);
            }
        }
        m_Driver->beginScene();
        drawBackground();           // Draw Background
        drawAxisLines();            // Draw XYZ Axis
        m_Scene->drawAll();         // Draw Scenegraph

        m_UserInterface->getGUIEnvironment()->drawAll();
        m_UserInterface->drawStatusLine();

        m_Driver->endScene();

        u32 sleepTime = timePerFrame - ( timer->getRealTime() - startTime );
        if( sleepTime > 0 && sleepTime < timePerFrame )
            m_Device->sleep( sleepTime, false );
    }
}
