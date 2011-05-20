/* client_sock.h - Client socket code, allowing software to connect to an
 *                 active server.
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * client_sock.h is the legal property of its developers, whose names
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

#include "../../main.h"
#include "player_data.h"
#include "data.h"
#include "error.h"

class client_socket
{
	int						sock;			// Local socket descriptor
	short					client_id;
	unsigned short			listen_port;
	struct sockaddr_in		server_addr;	// Server address
	struct sockaddr_in		recv_addr;		// Address of packet sender

	char			       *ip;				// Server IP address
	char					buffer[ 256 ];
	
#ifdef WIN32
	int						data_size;
#else
	socklen_t				data_size;
#endif

public:
							client_socket( unsigned int port, const char *ip );
						   ~client_socket();

	void					Send();
	void					send_player_data( player_data * );
};
