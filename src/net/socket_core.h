/* socket_core.h - Socket I/O allowing network communication
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * socket_core.h is the legal property of its developer.
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

#pragma once
#include <iostream>

#include "server_sock.h"
#include "client_sock.h"
#include "player_data.h"

#define SOCKET_SERVER	0x01
#define SOCKET_CLIENT	0x02
#define DEFAULT_IP		"127.0.0.1"

class socket_core
{

	short				mode_;
	server_socket	   *core_srv;	// Core server descriptor
	client_socket	   *core_cnt;	// Core socket descriptor

#ifdef WIN32
	void				init_ws2();
#endif

public:
						socket_core( short, const char *, unsigned short );
					   ~socket_core();
	
	short				mode();
	void				send_player_data( player_data * );
};
