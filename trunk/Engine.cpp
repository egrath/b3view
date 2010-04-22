#include "Engine.h"

/* //////////////////////////////////////////////////////////////////////////
   PRIVATE METHODS
   /////////////////////////////////////////////////////////////////////// */

void Engine::setupScene()
{
    // Setup Light
    ILightSceneNode *light = m_Scene->addLightSceneNode();
    light->setID( SIID_LIGHT );
    light->setLightType( ELT_DIRECTIONAL );
    light->getLightData().AmbientColor = SColorf( 0.2f, 0.2f, 0.2f );
    light->getLightData().DiffuseColor = SColorf( 0.8f, 0.8f, 0.8f );
    m_Scene->setAmbientLight( SColorf( 0.2f, 0.2f, 0.2f ));

    // Setup Camera
    ICameraSceneNode *camera = m_Scene->addCameraSceneNode( 0, vector3df( 0, 0, -10 ), vector3df() );
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
    dimension2d<u32> textSize = m_AxisFont->getDimension( L"X+" );
    m_AxisFont->draw( L"X+", rect<s32>( textPos, textSize ), SColor( 255, 255, 0, 0 ), true, true );

    m_Driver->setMaterial( *lineY );
    m_Driver->draw3DLine( vector3df(), vector3df( 0, 5, 0 ), SColor( 255, 0, 255, 0 ));
    textPos = m_Scene->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition( vector3df( 0, 5.2, 0 ));
    textSize = m_AxisFont->getDimension( L"Y+" );
    m_AxisFont->draw( L"Y+", rect<s32>( textPos, textSize ), SColor( 255, 0, 255, 0 ), true, true );

    m_Driver->setMaterial( *lineZ );
    m_Driver->draw3DLine( vector3df(), vector3df( 0, 0, 5 ), SColor( 255, 0, 0, 255 ));
    textPos = m_Scene->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition( vector3df( 0, 0, 5.2 ));
    textSize = m_AxisFont->getDimension( L"Z+" );
    m_AxisFont->draw( L"Z+", rect<s32>( textPos, textSize ), SColor( 255, 0, 0, 255 ), true, true );

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

void Engine::loadMesh( const wstring &fileName )
{
    if( m_LoadedMesh != 0 )
        m_LoadedMesh->remove();

    m_LoadedMesh = m_Scene->addAnimatedMeshSceneNode( m_Scene->getMesh( fileName.c_str() ));
}

void Engine::checkResize()
{
    if(( m_WindowSize->Width != m_Driver->getScreenSize().Width ) || ( m_WindowSize->Height != m_Driver->getScreenSize().Height ))
    {
        m_WindowSize->Width = m_Driver->getScreenSize().Width;
        m_WindowSize->Height = m_Driver->getScreenSize().Height;

        f32 aspectRatio = (f32) m_WindowSize->Width / m_WindowSize->Height;
        debug() << "Setting aspect to: " << aspectRatio << endl;
        m_Scene->getActiveCamera()->setAspectRatio( aspectRatio );
    }
}

/* //////////////////////////////////////////////////////////////////////////
   PUBLIC METHODS
   /////////////////////////////////////////////////////////////////////// */

Engine::Engine()
{
#if WIN32
    m_Device = createDevice( EDT_DIRECT3D9, dimension2d<u32>( 1024, 768 ), 32, false, false, false, 0 );
#else
	m_Device = createDevice( EDT_OPENGL, dimension2d<u32>( 1024, 768 ), 32, false, false, false, 0 );
#endif
    m_Device->setResizable( true );

    m_EventHandler = new EventHandler( m_Device );
    m_Device->setEventReceiver( m_EventHandler );

    m_Driver = m_Device->getVideoDriver();
    m_Scene = m_Device->getSceneManager();

	wstringstream windowTitle;
	windowTitle << L"Blitz3D Viewer [" << m_Driver->getName() << L"]";
    m_Device->setWindowCaption( windowTitle.str().c_str() );

    setupScene();

    // Setup User Interface
    m_UserInterface = new UserInterface( this );
    m_EventHandler->addEventReceiver( ERT_USERINTERFACE, m_UserInterface );

    // Setup 3D View
    m_View = new View( this );
    m_EventHandler->addEventReceiver( ERT_3DVIEW, m_View );

    // Load font for displaying Axis names
    m_AxisFont = m_Device->getGUIEnvironment()->getFont( "arial.xml" );

    // Set Engine enabled
    m_RunEngine = true;

    // Load test model
    m_LoadedMesh = 0;
    loadMesh( L"test.b3d" );

    // Store actual window size
    m_WindowSize = new dimension2d<u32>();
    m_WindowSize->Width = m_Driver->getScreenSize().Width;
    m_WindowSize->Height = m_Driver->getScreenSize().Height;
}

Engine::~Engine()
{
    m_Device->drop();
    delete m_WindowSize;
}

void Engine::run()
{
    u32 timePerFrame = ( u32 ) ( 1000.0f / 60 );
    ITimer *timer = m_Device->getTimer();       

    // Run the Device with 60 frames/sec
    while( m_Device->run() && m_RunEngine )
    {
        u32 startTime = timer->getRealTime();

        checkResize();

        m_Driver->beginScene();
        drawBackground();           // Draw Background
        drawAxisLines();            // Draw XYZ Axis
        m_Scene->drawAll();         // Draw Scenegraph
        m_UserInterface->getGUIEnvironment()->drawAll();

        m_Driver->endScene();

        u32 sleepTime = timePerFrame - ( timer->getRealTime() - startTime );
        if( sleepTime > 0 && sleepTime < timePerFrame )
            m_Device->sleep( sleepTime, false );
    }
}
