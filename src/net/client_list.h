/* client_list.h - Data set holding data of connected clients
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * client_list.h is the legal property of its developers, whose names
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

#ifdef WIN32
	#include <winsock2.h>
#else
	#include <sys/socket.h>
	#include <arpa/inet.h>
#endif

#include <iostream>
#include <string.h>
#include <string>

#include "player_data.h"

/*
	START COMM STATUS CODES
 */

#define						SCK_STAT_ITEM_EMPTY  0x00
#define						SCK_STAT_INCOME_WAIT 0x01

class client_list
{
	std::string				client_id_;		// ID of connected client
	int						stream_stat_;	// Do we listen for her?
	struct sockaddr_in		client_addr_;	// Client socket address
	
	player_data				client_game_data_;

	void					zero_address();	// Purge item address space

public:
							client_list( struct sockaddr_in * );
						   ~client_list();

	bool					operator==( const std::string &addr )const;

	void					set_player_data( player_data * );
	int						get_status();
	void					dc_client();
	std::string				get_ip();
};
