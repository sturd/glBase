/* tsz_pad.h
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 *
 * tsz_pad.h is the legal property of its developer.
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

#ifndef TSZ_PAD
#define TSZ_PAD

#include <windows.h>
#include <XInput.h>
#include <iostream>

#include "input_type.h"

#define GAMEPAD_LEFT_THUMB_X  0x01
#define GAMEPAD_LEFT_THUMB_Y  0x02
#define GAMEPAD_RIGHT_THUMB_X 0x03

class tsz_pad : public input_type
{
	DWORD				dw_result[ 4 ];
	XINPUT_STATE		state[ 4 ];
	bool				assigned[ 4 ];	// Control assignments

public:
						tsz_pad();
	short				update_status();
	bool				is_connected( unsigned short );

	bool				wants_in( unsigned short pad );

	bool				button_down( unsigned short, WORD );
	short				analog_state( unsigned short, short );
};

#endif /* TSZ_PAD */