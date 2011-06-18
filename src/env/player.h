/* player.h
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 *
 * player.h is the legal property of its developer.
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

#ifndef PLAYER_H
#define PLAYER_H

#include "../sprite/sprite.h"
#include "../input/input_handler.h"
#include <iostream>

class player : public sprite
{
	char		   *input;
	short			input_port;


	void			handle_input();
	void			handle_gamepad();
	void			handle_keyboard();
public:
					player( int xPos, int yPos, input_init_data device );
	void			set_device( const char *device_ptr );
	void			process_player();
};

#endif
