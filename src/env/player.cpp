/* player.cpp
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 *
 * player.cpp is the legal property of its developer.
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

#include "player.h"

player::player( int xPos, int yPos, input_init_data device ) :
		sprite( "media/image/run.tga", xPos, yPos, 8, 0 )
{
	input_port = device.port;
}

/*
	set_device() - Pass the device pointer to the player class
 */
void player::set_device( const char *device_ptr )
{
	input = ( char * )device_ptr;
}

/*
	handle_input() - Determine the input type assigned to the class
					 and execute the relavent routine to handle inputs.
 */
void player::handle_input()
{
#ifdef WIN32
	if( ( ( input_type * )input )->get_input_type() == INPUT_TYPE_GAMEPAD )
		handle_gamepad();
#endif
	if( ( ( input_type * )input )->get_input_type() == INPUT_TYPE_KEYBOARD )
		handle_keyboard();
}

/*
	handle_gamepad() - Handle input as a tsz_pad type, and listen
					   for inputs on the addressed pad.
 */
void player::handle_gamepad()
{
#ifdef WIN32
	tsz_pad *pad = ( tsz_pad * )input;	// Cast tsz_pad type from input pointer

	// Check if 'back' button is down on pad.  Quits program for now.
	if( pad->button_down( input_port, XINPUT_GAMEPAD_BACK ) )
		exit( 0 );

	short x_state = pad->analog_state( input_port, GAMEPAD_LEFT_THUMB_X );

	if( x_state > 18 )
		_xVel += 4;
	else if( x_state < -18 )
		_xVel -= 4;
	else
	{
		if( _xVel > 0 )
			_xVel -= 4;
		else if( _xVel < 0 )
			_xVel += 4;
	}
#endif
}

void player::handle_keyboard()
{

	keyboard *kbd = ( keyboard * )input;
	kbd->update_status();


	if( kbd->button_down( KB_ESCAPE ) )
		exit( 0 );

	if( kbd->button_down( KB_D ) )
		SetXVel( 15 );
	if( kbd->button_down( KB_A ) )
		SetXVel( -15 );
}

void player::process_player()
{
	handle_input();
	DrawImage();
}
