/* error.cpp - Error output code.  Prints socket errors and terminates program.
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * error.cpp is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
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

#include "error.h"

void SocketError( std::string error_msg, int error = 0 )
{
	std::cout << "Error: " << error_msg << std::endl;
	std::cout << "Terminating..." << std::endl;
	exit( error );
}

void SocketError( std::string error_msg )
{
	std::cout << "Error: " << error_msg << std::endl;
	std::cout << "Terminating..." << std::endl;
	exit( 0 );
}
