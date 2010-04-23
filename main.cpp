#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "Engine.h"

wchar_t * getWideCharString( char *str );

#ifdef WIN32
#include <Windows.h>
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
#else
int main( int argc, char **argv )
#endif
{
	// Parse commandline to check if a filename argument has been passed
#ifdef WIN32
	int argc;
	char **argv;

	LPWSTR *args;
	args = CommandLineToArgvW( GetCommandLineW(), &argc );

	argv = ( char ** ) malloc( sizeof( char * ) * argc );
	for( int index = 0; index < argc; index ++ )
	{		
		int argumentBufferLength = wcslen( args[index] ) + 1;
		argv[index] = ( char * ) malloc( sizeof( char ) * argumentBufferLength );
		sprintf_s( argv[index], argumentBufferLength, "%ws", args[index] );
	}

	LocalFree( args );
#endif

    Engine *engine = new Engine();
	if( argc >= 2 )
	{
		wchar_t *initialFileName = getWideCharString( argv[1] );
		engine->loadMesh( wstring( initialFileName ));
		free( initialFileName );
	}
	else
		engine->loadMesh( L"test.b3d" );

    engine->run();

    delete engine;

#ifdef WIN32
	for( int index = 0; index < argc; index ++ )
		free( argv[index] );
	free( argv );
#endif
}

wchar_t * getWideCharString( char *str )
{
	wchar_t *dest = ( wchar_t * ) malloc( sizeof( wchar_t ) * ( strlen( str ) + 1 ));

    int resultSize = mbstowcs( 0, str, strlen( str ));
    mbstowcs( dest, str, strlen( str ));

    dest[resultSize] = '\0';

	return dest;
}

