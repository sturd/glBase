/* main.cpp - Main entry point to software, SDL initialisation
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://www.sturd.co.uk/sonicjs/
 *
 * main.cpp is the legal property of its developer.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include <iostream>

#include "main.h"
#include "src/net/socket_core.h"
#include "src/env/leveldata.h"

using namespace std;

init_sock_dat::init_sock_dat( short mode, char *ip, unsigned short port )
{
	sock_mode = mode;
	targ_addr = ip;
	targ_port = port;
}

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

    screen = SDL_SetVideoMode( WIDTH, HEIGHT, 32, SDL_OPENGL /*| SDL_FULLSCREEN */ );
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
		Lvl1 = new LevelData( new init_sock_dat( SOCKET_SERVER,
												 "127.0.0.1",
												 1987			) );

	else if( !strcmp( args[ 1 ], "--client" ) )
	{
		if( !args[ 2 ] )
			SocketError( "Invalid arguments for client mode." );
		
		Lvl1 = new LevelData( new init_sock_dat( SOCKET_CLIENT,
												 args[ 2 ],
												 1987			) );
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
