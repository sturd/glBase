#include <iostream>

#include "main.h"
#include "src/net/socket_core.h"
#include "src/env/leveldata.h"

using namespace std;

bool InitAudio()
{
	int Rate = 44100;
	Uint16 Format = AUDIO_S16;
	int Channels = 2;
	int Buffer = 4096;
	if( Mix_OpenAudio( Rate, Format, Channels, Buffer ) )
	{
		cout << "Unable to open audio!" << endl;
		return false;
	}

	return true;
}

bool InitOGLVideo( SDL_Surface *screen )
{

    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0 ) {
		cout << "Unable to initialize SDL: " << SDL_GetError();
		return false;
    }

	SDL_WM_SetCaption( "Sturd's OpenGL Sandbox", NULL );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    screen = SDL_SetVideoMode( WIDTH, HEIGHT, 32, SDL_OPENGL /*| SDL_FULLSCREEN*/ );
    if ( !screen )
	{
		cout << "Unable to set video mode: " << SDL_GetError();
		return false;
	}

    // Set the OpenGL state after creating the context with SDL_SetVideoMode
	glEnable( GL_TEXTURE_2D );
    glViewport( 0, 0, WIDTH, HEIGHT );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

	return true;
}

void SDLMain_Loop( char *args[] )
{
	LevelData *Lvl1;
	if( !args[ 1 ] )
		SocketError( "No arguments found." );

	else if( !strcmp( args[ 1 ], "--server" ) )
		Lvl1 = new LevelData( SOCKET_SERVER );

	else if( !strcmp( args[ 1 ], "--client" ) )
	{
		if( !args[ 2 ] )
			SocketError( "Invalid arguments for client mode." );

		Lvl1 = new LevelData( SOCKET_CLIENT );
	}
	//Mix_Music *music = Mix_LoadMUS( "summer.ogg" );
	//Mix_Music *ring = Mix_LoadMUS( "ring.ogg" );

	//Mix_PlayMusic( music, 0 );

	Lvl1->Execute();
	
}

int main( int argc, char *argv[] )
{
 	SDL_Surface *screen = new SDL_Surface;

	if( !InitOGLVideo( screen ) )
		exit( 0 );

	if( !InitAudio() )
		exit( 0 );

	SDLMain_Loop( argv );
    SDL_Quit();
    
	return 0;
}
