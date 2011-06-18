/* Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 *
 * input_type.h is the legal property of its developer.
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

#ifndef INPUT_TYPE_H
#define INPUT_TYPE_H

#define INPUT_TYPE_KEYBOARD		0x01
#define INPUT_TYPE_GAMEPAD		0x02
#define INPUT_TYPE_SMARTPHONE	0x03

class input_type
{
	short		input_mode;			// Input descriptor

public:
				input_type( short mode );
	short		get_input_type();
};

#endif /* INPUT_TYPE_H */
