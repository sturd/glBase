/* keyboard.h
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 *
 * keyboard.h is the legal property of its developer.
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

#include <SDL/SDL.h>

#include "input_type.h"

#define KB_W		SDLK_w
#define KB_A		SDLK_a
#define KB_S		SDLK_s
#define KB_D		SDLK_d

#define KB_UP		SDLK_UP
#define KB_DOWN		SDLK_DOWN
#define KB_LEFT		SDLK_LEFT
#define KB_RIGHT	SDLK_RIGHT

#define KB_SPACE	SDLK_SPACE

#define KB_RETURN	SDLK_RETURN
#define KB_ESCAPE	SDLK_ESCAPE

class keyboard : public input_type
{
	bool			assigned;
	bool			key_down[ 300 ];
public:
					keyboard();
	void			update_status();
	bool			button_down( short button );
	bool			wants_in();
};