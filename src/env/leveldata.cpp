// Filename:	leveldata.cpp
// Author:		Craig Sturdy
// ID:			N0178138
// Version:		0.1

// Description:	Contains implementation of game level data

#include <iostream>
#include <fstream>

using namespace std;

#include "leveldata.h"

LevelData::LevelData( int socket_mode )
{
	sonic = new sprite( "media/image/run.tga", 100, 100, 8 );
	net_core = new socket_core( socket_mode, "192.168.0.3", 1987 );
	key_right_down = false;
	key_left_down = false;
	key_up_down = false;
	key_down_down = false;
}

void LevelData::LoadData()
{
	// Declaration of config data set
	char LVL_ID[ MAX_LENGTH ];
	char DAT_ID[ MAX_LENGTH ];
	char Path[ MAX_LENGTH ];
	int xPos = 0; int yPos = 0;

	// Load config file
	ifstream level( LVL_PTH, ios::in );
	ifstream image( DAT_PTH, ios::in );

	bool Match = true;

	// Scan level file from beginning to end
	while( !level.eof() )
	{
		memset( LVL_ID, 0, sizeof( LVL_ID ) );
		memset( DAT_ID, 0, sizeof( DAT_ID ) );
		memset( Path, 0, sizeof( Path ) );
		// Load contained values from file
		level >> LVL_ID >> xPos >> yPos;

		while( !image.eof() )
		{
			image >> DAT_ID >> Path;

			Match = true;
			// Possible instability with different ID lengths...
			for( int ChrScan = 0; ChrScan < sizeof( DAT_ID ); ++ChrScan )
			{
				if( LVL_ID[ ChrScan ] != DAT_ID[ ChrScan ] )
				{
					// If mismatch found, set flag
					// to false and break from loop
					Match = false;
					break;
				}
			}
		}

	}
}

void LevelData::Execute()
{

	SDL_Event KeyEvent;
	bool Running = true;

	// Loop to contain whole running of game (maybe)
	while( Running )
	{
		// Listen for keystrokes
		while( SDL_PollEvent( &KeyEvent ) )
		{
			switch( KeyEvent.type )
			{
			case SDL_KEYDOWN:	/* Keyboard Press Event */
				switch( KeyEvent.key.keysym.sym )
				{
					case SDLK_ESCAPE:
						// Escape pressed, break from main loop
						Running = false;
						break;

					case SDLK_RIGHT:
						key_right_down = true;
						break;
					case SDLK_LEFT:
						key_left_down = true;
						break;
					case SDLK_UP:
						key_up_down = true;
						break;
					case SDLK_DOWN:
						key_down_down = true;
						break;
					default:
						break;
				}
			default:
				break;

			case SDL_KEYUP:	/* Keyboard Release Event */
				switch( KeyEvent.key.keysym.sym )
				{
					case SDLK_RIGHT:
						key_right_down = false;
						break;
					case SDLK_LEFT:
						key_left_down = false;
						break;
					case SDLK_UP:
						key_up_down = false;
						break;
					case SDLK_DOWN:
						key_down_down = false;
						break;
					default:
						break;
				}
			}
		}

		glClearColor( 0.53125f, 0.546875f, 0.53125, 0.5f );
		glClear( GL_COLOR_BUFFER_BIT );

		if( key_right_down )
			sonic->SetXVel( sonic->GetXVel() + 1 );
			
		else
			sonic->SetXVel( sonic->GetXVel() - 1 );

		if( key_left_down )
			sonic->SetXVel( sonic->GetXVel() - 1 );
			
		else
			sonic->SetXVel( sonic->GetXVel() + 1 );


		sonic->DrawImage();

		SDL_GL_SwapBuffers();

		SDL_Delay( 85 );
	}
	
	exit( 0 );
}
