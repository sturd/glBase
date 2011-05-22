/* data.h - Network data code, describes data formatting when transferring
 *			over network.
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * data.h is the legal property of its developers, whose names
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

#pragma once

#include <string>

#include "player_data.h"

#define PACKET_STAT_CONN_BLN 0x00	// Blank packet set by default constructor
#define PACKET_STAT_CONN_NEW 0x01	// Packet requesting new connection
#define PACKET_STAT_CONN_DIE 0x02	// Packet requesting disconnect
#define PACKET_STAT_CONN_ACC 0x03	// Packet accepting connection
#define PACKET_STAT_CONN_EXI 0x04	// Connection already open
#define PACKET_STAT_CONN_DAT 0x05	// Player data packet

#define PLAYER_DATA_SIZE 40

class net_data
{
	short					packet_status;	// Packet status header
	short					client_id_;
	char					packet_content[ PLAYER_DATA_SIZE ];

public:
							net_data();
							net_data( short );
							net_data( player_data *, const short & );

	bool 					operator==( const short & )const;

	void					set_status( short );
	short					get_client_id();
	player_data			   *get_player_data();
};
