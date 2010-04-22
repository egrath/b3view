#include "Engine.h"

#ifdef WIN32
#include <Windows.h>
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
#else
int main( int argc, char **argv )
#endif
{
    Engine *engine = new Engine();
    engine->run();

    delete engine;
}

