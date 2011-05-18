/* server_sock.cpp - Non-blocking socket, polls in separate thread for clients
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * server_sock.cpp is the legal property of its developers, whose names
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

#include "server_sock.h"

server_socket::server_socket( unsigned short port )
{
	client_count = 0;
	is_done_ = false;

	if( ( sock = socket( PF_INET, SOCK_DGRAM, IPPROTO_UDP ) ) < 0 )
		SocketError( "Unable to initialise socket.", 3 );

#ifdef WIN32 /* Non blocking socket initialisation */
	u_long block_mode = 1;
	if( ioctlsocket( sock, FIONBIO, &block_mode ) < 0 )
		SocketError( "Unable to initiate nonblocking socket.", 5 );
#else
	if( fcntl( sock, F_SETFL, O_NONBLOCK | FASYNC ) < 0 )
		SocketError( "Unable to initiate nonblocking socket." );
#endif

	local_addr = init_local_address( port );

	// Bind the local address structure to the socket
	if( bind( sock, ( struct sockaddr * )&local_addr, 
		sizeof( local_addr ) ) < 0 )
		SocketError( "Unable to bind local address.", 8 );

	// Zero out client address structure
	for( int i = 0; i < MAX_CLIENTS; ++i )
		client_addr_lst[ i ] = 0;

	// Bind listen routine to thread
	incoming_thread =
		new boost::thread(
			boost::bind( &server_socket::listen, this )
		);
}

server_socket::~server_socket()
{
#ifdef WIN32
	WSACleanup();
#else
	close( sock );
#endif
	// Destroy running thread on close
	incoming_thread->detach();
}

/*
	init_local_address() - Initialises local address structure.
 */
struct sockaddr_in server_socket::init_local_address( unsigned short port )
{
	struct sockaddr_in temp;
	memset( &temp, 0, sizeof( temp ) );
	temp.sin_family			= AF_INET;
	temp.sin_addr.s_addr	= htonl( INADDR_ANY );
	temp.sin_port			= htons( port );
	return temp;
}

/*
	listen() - Private to server_socket, executed within a boost::thread
			   allowing paralell management of incoming data.
 */
void server_socket::listen()
{
	net_data temp_data;
	data_size = sizeof( inbnd_addr );

	std::cout << "Listening..." << std::endl;
	for( ; !is_done_ ; )
		if( recvfrom( sock, ( char * )&temp_data, 255, 0,
			( struct sockaddr * )&inbnd_addr, &data_size ) >= 0 )
		{
			// Packet is from a new client, requesting to join
			if( temp_data == PACKET_STAT_CONN_NEW )
				handle_new( &temp_data, &inbnd_addr );
			else if( temp_data == PACKET_STAT_CONN_DAT )
			{
				player_data *tmp_dat = temp_data.get_player_data();
				std::cout << tmp_dat->get_height() << std::endl;
			}
		}
}

bool server_socket::is_done()
{
	return is_done_;
}

void server_socket::handle_new( net_data *data, struct sockaddr_in *addr )
{
	bool is_unique = true;
	/*
		Scan active clients and ensure the client
		requesting the connection is not already
		allocated in the list.

		NOTE:- May have to find a better way
			   to identify clients (other than IP)
			   as multiple connections may requested
			   from same network.  Consider generating
			   hash ID for better identification
	*/

	for( int i = 0; i < MAX_CLIENTS; ++i )
		if( client_addr_lst[ i ] )
			if( client_addr_lst[ i ]->get_ip() == 
				inet_ntoa( addr->sin_addr ) )
			{
				is_unique = false;
				send_reply( new net_data( PACKET_STAT_CONN_EXI ), addr );
				break;
			}

	// Client list is not full and is unique, so
	// activate a new address structure and store it.
	if( client_count < MAX_CLIENTS && is_unique )
	{
		client_addr_lst[ client_count ] =
			new client_list( addr );
		// Inform client of successful connection
		send_reply( new net_data( PACKET_STAT_CONN_ACC ), addr );
		++client_count;
	}
}

/*
	send_reply() - Sends reply back to specified client, with requested data
 */
void server_socket::send_reply( net_data *data, struct sockaddr_in *addr )
{
#ifdef WIN32
	int tmp_data_size = sizeof( *data );
#else
	socklen_t tmp_data_size = sizeof( *data );
#endif

	if( sendto( sock, ( const char * )data, tmp_data_size, 0,
		( struct sockaddr * )addr, sizeof( *addr ) ) != tmp_data_size )
		SocketError( "Unable to send data." );
}
