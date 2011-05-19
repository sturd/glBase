/* client_list.cpp - Data set holding data of connected clients
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * client_list.cpp is the legal property of its developers, whose names
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

#include "client_list.h"

client_list::client_list( struct sockaddr_in *client_addr )
{
	if( client_addr )
	{
		/*
			Client address exists, save a copy locally
			and set list item to open.
		 */
		zero_address();
		client_addr_ = *client_addr;
		stream_stat_ = SCK_STAT_INCOME_WAIT;
		client_id_   = std::string( inet_ntoa( client_addr_.sin_addr ) );
		std::cout << client_id_ << std::endl;
	}
	else
		stream_stat_ = SCK_STAT_ITEM_EMPTY;
}

client_list::~client_list()
{
	zero_address();
	stream_stat_ = SCK_STAT_ITEM_EMPTY;
}

void client_list::zero_address()
{
	// Zero out address structure for initialisation
	memset( &client_addr_, 0, sizeof( client_addr_ ) );
}

/*
	== - Determine equality of list item with another
		 item.  Should only be used when establishing
		 new connection with client.
		 Compare string format IP address for time being...
 */
bool client_list::operator==( const std::string &addr )const
{
	return ( addr == client_id_ );
}

/*
	get_player_data() - Expose player data in item to external
						gameplay process.
 */
player_data *client_list::get_player_data()
{
	return &client_game_data_;
}

void client_list::set_player_data( player_data *data )
{
	client_game_data_ = *data;
}

/*
	get_status() - Determine client is connected.  Allows
				   server to pass client object and avoid
				   being blocked by a non-responsive client.
 */
int client_list::get_status()
{
	return stream_stat_;
}

/*
	dc_client() - Delete address structure and set stream
				  to closed to prevent poll blocking.
 */
void client_list::dc_client()
{
	zero_address();
	stream_stat_ = SCK_STAT_ITEM_EMPTY;
}

/*
	get_ip() - Determine IP address of client in order to
			   fire message at their machine.
 */
std::string client_list::get_ip()
{
	return std::string( inet_ntoa( client_addr_.sin_addr ) );
}
