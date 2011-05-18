/* server_sock.h - Non-blocking socket, polls in separate thread for clients
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * server_sock.h is the legal property of its developers, whose names
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
#include <fcntl.h>

#include <string.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/locks.hpp>

#include "data.h"
#include "error.h"
#include "client_list.h"

#define MAX_CLIENTS 6

class server_socket
{

	struct sockaddr_in	local_addr;			// Local address
	struct sockaddr_in	inbnd_addr;			// Inbound address

	boost::mutex		data_mutex;			// Mutex for synchronising data access
	boost::thread	   *incoming_thread;	// Thread listening for new clients

	int					client_count;		// Number of clients currently connected
	client_list		   *client_addr_lst[ MAX_CLIENTS ];

	bool				is_done_;

	struct sockaddr_in	init_local_address( unsigned short );
	void				send_reply( net_data *, struct sockaddr_in * );


#ifdef WIN32
	SOCKET				sock;
	int					data_size;			// Size of incoming data
#else
	int					sock;				// Socket descriptor
	socklen_t           data_size;
#endif
	
	char				buffer[ 255 ];		// Buffer for incoming data...
	int					recv_data_size;		// Size of recieved data

	void				handle_new( net_data *, struct sockaddr_in * );
	void				handle_game_data( net_data *, struct sockaddr_in * );
	void				listen();			// Listen for incoming data
public:
						server_socket( unsigned short port );
					   ~server_socket();
					   
	void				lock_mutex();		// Provides external access to data mutex
	void				unlock_mutex();

	bool				is_done();
};
