/* Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * leveldata.cpp is the legal property of its developer.
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
#include <fstream>

using namespace std;

#include "leveldata.h"

LevelData::LevelData( int socket_mode )
{
	net_core = new socket_core( socket_mode, "127.0.1.1", 1987 );

	if( net_core->mode() == SOCKET_SERVER )
	{
		sonic = new sprite( "media/image/run.tga", 100, 100, 8 );
		client_sprite = new sprite( "media/image/run.tga", 250, 250, 8 );
	}
	else if( net_core->mode() == SOCKET_CLIENT )
	{
		sonic = new sprite( "media/image/run.tga", 250, 250, 8 );
		player_data *new_data = sonic->get_player_data();
		net_core->send_player_data( new_data );
	}
	
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
		player_data tmp_plyr_data;
		if( net_core->mode() == SOCKET_SERVER )
		{
			tmp_plyr_data.set_player_data(
				net_core->send_player_data( sonic->get_player_data() ) );
			if( tmp_plyr_data.get_height() != 0 )
				client_sprite->set_player_data( &tmp_plyr_data );

			client_sprite->DrawImage();
		}
		else if( net_core->mode() == SOCKET_CLIENT )
		{
			player_data *plr_data = sonic->get_player_data();
			net_core->send_player_data( plr_data );
		}


		SDL_GL_SwapBuffers();

		SDL_Delay( 85 );
	}
	
	exit( 0 );
}
