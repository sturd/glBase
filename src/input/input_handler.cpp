/* Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 *
 * input_handler.cpp is the legal property of its developer.
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

#include "input_handler.h"

#include <iostream>

input_handler::input_handler()
{
#ifdef WIN32
	game_pad = new tsz_pad();
	pad_count = 0;
#endif

	kbd		 = new keyboard();
}

/*
	wants_in() - Returns the type and location of the first
				 un-used, plugged device that is requesting
				 to join.
 */
input_init_data input_handler::wants_in()
{
	input_init_data tmp_data;
	memset( &tmp_data, 0, sizeof( input_init_data ) );

#ifdef WIN32
	// Poll connected gamepads to test for
	// join request.
	for( int i = 0; i < 4; ++i )
		if( game_pad->is_connected( i ) )
			if( game_pad->wants_in( i ) )
			{
				tmp_data.mode = INPUT_TYPE_GAMEPAD;
				tmp_data.port = i;
				return tmp_data;
			}
#endif

	kbd->update_status();
	if( kbd->wants_in() )
	{
		tmp_data.mode = INPUT_TYPE_KEYBOARD;
		return tmp_data;
	}
	return tmp_data;
}

char *input_handler::device_pointer( input_init_data target )
{
	// Return generic pointer to gamepad object for access from
	// player class
#ifdef WIN32
	if( target.mode == INPUT_TYPE_GAMEPAD )
		return ( char * )game_pad;
#endif

	if( target.mode == INPUT_TYPE_KEYBOARD )
		return ( char * )kbd;

	return 0;
}
