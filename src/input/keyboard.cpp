/* keyboard.cpp
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 *
 * keyboard.cpp is the legal property of its developer.
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

#include "keyboard.h"

keyboard::keyboard() : input_type( INPUT_TYPE_KEYBOARD )
{
	assigned = false;

	for( int i = 0; i < 300; ++i )
		key_down[ i ] = false;
}

void keyboard::update_status()
{
	SDL_Event KeyEvent;
	while( SDL_PollEvent( &KeyEvent ) )
	{
		switch( KeyEvent.type )
		{
		case SDL_KEYDOWN:
			key_down[ KeyEvent.key.keysym.sym ] = true;
			break;
		case SDL_KEYUP:
			key_down[ KeyEvent.key.keysym.sym ] = false;
			break;
		}
	}
}

bool keyboard::button_down( short button )
{
	return key_down[ button ];
}

bool keyboard::wants_in()
{
	if( !assigned &&
		 button_down( KB_RETURN ) )
	{
		assigned = true;
		return true;
	}

	return false;
}
