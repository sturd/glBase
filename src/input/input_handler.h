/* Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 *
 * input_handler.h is the legal property of its developer.
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

#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#ifdef WIN32
#include "tsz_pad.h"
#endif

#include "keyboard.h"

struct input_init_data
{
	short mode;
	short port;
};

class input_handler
{

#ifdef WIN32
	tsz_pad			   *game_pad;
	short				pad_count;
#endif

	keyboard		   *kbd;

public:
						input_handler();
	input_init_data		wants_in();
	char			   *device_pointer( input_init_data target );
};

#endif /* INPUT_HANDLER_H */
