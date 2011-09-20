/* server_sock.cpp - Non-blocking socket, polls in separate thread for clients
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * server_sock.cpp is the legal property of its developer.
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
	// Initialise client_count as 1, reserving first place in
	// list for the server player.
	client_count = 1;
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

	long loopCount = 0;
	std::cout << "Listening..." << std::endl;
	for( ; !is_done_ ; )
		if( recvfrom( sock, ( char * )&temp_data, 255, 0,
			( struct sockaddr * )&inbnd_addr, &data_size ) >= 0 )
		{
			// Packet is from a new client, requesting to join
			if( temp_data == PACKET_STAT_CONN_NEW )
				handle_new( &temp_data, &inbnd_addr );
			else if( temp_data == PACKET_STAT_CONN_DAT )
				handle_game_data( &temp_data, &inbnd_addr );
	}
}

short server_socket::get_client_count()
{
	return ( short )client_count;
}

bool server_socket::is_done()
{
	return is_done_;
}

/*
	get_player_data() - Allow level_data object to call upon required
						player data for displaying on screen.
 */
player_data *server_socket::get_player_data( short client_id )
{
	player_data *rtn_data = new player_data;
	data_mutex.lock();
	for( int i = 0; i < MAX_CLIENTS; ++i )
		if( client_addr_lst[ i ] )
			if( client_addr_lst[ i ]->get_id() !=
				client_id	)
			{	// Make a local copy of the needed player data to allow
				// unlocking of the mutex before return.
				rtn_data->SetPlayerData(
					client_addr_lst[ i ]->get_player_data() );
				//std::cout << "X: " << rtn_data.get_x() << std::endl;
				break;
			}
	data_mutex.unlock();

	return rtn_data;
}

/*
	update_local_player() - Make local player data available to socket
							for transmission to connected clients.
 */
void server_socket::update_local_player( player_data *data )
{
	data_mutex.lock();
	short tmp_id = 0;
	if( !client_addr_lst[ 0 ] )
		client_addr_lst[ 0 ] = new client_list( &local_addr, tmp_id );

	client_addr_lst[ 0 ]->set_player_data( data, tmp_id );
	data_mutex.unlock();
}

void server_socket::handle_new( net_data *data, struct sockaddr_in *addr )
{
	data_mutex.lock();
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

	for( int i = 1; i < MAX_CLIENTS; ++i )
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
		short tmp_cc = ( short )client_count;
		client_addr_lst[ client_count ] =
			new client_list( addr, tmp_cc );
		player_data *tmp_pl_data = new player_data();
		tmp_pl_data->SetPlayerData(
			client_addr_lst[ client_count ]->get_player_data() );
		net_data *tmp_net_data = new net_data(
			tmp_pl_data,
			tmp_cc );
		tmp_net_data->set_status( PACKET_STAT_CONN_ACC );
		// Inform client of successful connection
		send_reply( tmp_net_data, addr );
		++client_count;
	}
	data_mutex.unlock();
}

/*
	handle_game_data() - Place incoming game data into it's corresponding
						 structure in the client list.
						 TODO:- Finalise algorithm constructing a packet
						 		containing relevant game data for
						 		the waiting client.
 */
void server_socket::handle_game_data( net_data *data, struct sockaddr_in *addr )
{
	player_data *tmp_data = new player_data();
	tmp_data->SetPlayerData( data->get_player_data() );
	
	short		 tmp_id	      = data->get_client_id();
	data_mutex.lock();
	for( int i = 0; i < MAX_CLIENTS; ++i )
		if( client_addr_lst[ i ] )
			if( client_addr_lst[ i ]->get_id() ==
				tmp_id )
			{
				client_addr_lst[ i ]->set_player_data( 
					tmp_data,
					tmp_id );
				break;
			}
	data_mutex.unlock();
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

	std::cout << data->get_client_id() << std::endl;

	if( sendto( sock, ( const char * )data, tmp_data_size, 0,
		( struct sockaddr * )addr, sizeof( *addr ) ) != tmp_data_size )
		SocketError( "Unable to send data." );
}
