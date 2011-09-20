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

LevelData::LevelData( init_sock_dat *socket_data )
{
	net_core = new socket_core( socket_data->sock_mode,
								socket_data->targ_addr,
								socket_data->targ_port );
								
	inputs = new input_handler();

	for( int i = 0; i < 6; ++i )
		player_sprite[ i ] = 0;
	player_count = 0;
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

	//SDL_Event KeyEvent;
	bool Running = true;

	// Loop to contain whole running of game (maybe)
	while( Running )
	{
	
		init_device = inputs->wants_in();
		if( init_device.mode != 0 )
		{
			player_sprite[ player_count ] = new player( 100, 100, init_device );
			player_sprite[ player_count ]->set_device(
				inputs->device_pointer( init_device ) );

			++player_count;
		}

		glClearColor( 0.53125f, 0.546875f, 0.53125, 0.5f );

		glClear( GL_COLOR_BUFFER_BIT );

		for( int i = 0; i < player_count; ++i )
			player_sprite[ i ]->process_player();


		SDL_GL_SwapBuffers();

		SDL_Delay( 85 );
	}
	
	exit( 0 );
}
