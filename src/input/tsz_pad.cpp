/* tsz_pad.cpp
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 *
 * tsz_pad.cpp is the legal property of its developer.
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

#include "tsz_pad.h"

tsz_pad::tsz_pad() : input_type( INPUT_TYPE_GAMEPAD )
{
	for( int i = 0; i < 4; ++i )
		assigned[ i ] = false;

	update_status();
}

short tsz_pad::update_status()
{
	short pad_count = 0;
	for( int i = 0; i < 4; ++i )
	{
		memset( &state[ i ], 0, sizeof( XINPUT_STATE ) );
		dw_result[ i ] = XInputGetState( i, &state[ i ] );

		if( is_connected( i ) )
			++pad_count;
	}
	return pad_count;
}

/*
	bool is_connected() - Returns true if requested pad is physically
						  connected to the machine.
 */
bool tsz_pad::is_connected( unsigned short pad )
{
	if( dw_result[ pad ] == ERROR_SUCCESS )
		return true;

	return false;
}

/*
	bool wants_in() - Returns true if pad is unassigned
					  and the start button is being pressed.
 */
bool tsz_pad::wants_in( unsigned short pad )
{
	update_status();
	if( !assigned[ pad ] &&
		    state[ pad ].Gamepad.wButtons == XINPUT_GAMEPAD_START )
	{
		assigned[ pad ] = true;	
		return true;
	}

	return false;
}

/*
	bool button_down() - Returns true if the requested pad and
						 the button in question is being pressed.
 */
bool tsz_pad::button_down( unsigned short pad, WORD button )
{
	if( state[ pad ].Gamepad.wButtons == button )
		return true;

	return false;
}

short tsz_pad::analog_state( unsigned short pad, short button )
{
	short tmp_val = 0;
	switch( button )
	{
	case GAMEPAD_LEFT_THUMB_X:
		tmp_val = state[ pad ].Gamepad.sThumbLX;
		break;
	case GAMEPAD_LEFT_THUMB_Y:
		tmp_val = state[ pad ].Gamepad.sThumbLY;
		break;
	case GAMEPAD_RIGHT_THUMB_X:
		tmp_val = state[ pad ].Gamepad.sThumbRX;
		break;
	}

	if( tmp_val / 1000 <= 4 &&
		tmp_val / 1000 >= -4  )
		return 0;

	return tmp_val / 1000;
}