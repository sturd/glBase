/* client_sock.cpp - Client socket code, allowing software to connect to an
 *                   active server.
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * client_sock.cpp is the legal property of its developers, whose names
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

#include "client_sock.h"

client_socket::client_socket( unsigned int port, const char *ip )
{
	if( ( sock = socket( PF_INET, SOCK_DGRAM, IPPROTO_UDP ) ) < 0 )
		SocketError( "Unable to initialise socket." );

	memset( &server_addr, 0, sizeof( server_addr ) );
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr( ip );
	server_addr.sin_port = htons( port );
}

client_socket::~client_socket()
{
#ifdef WIN32
	WSACleanup();
#else
	close( sock );
#endif
}

void client_socket::Send()
{
	net_data newData( PACKET_STAT_CONN_NEW );

	data_size = sizeof( newData );
	int recv_data_size = 0;

	if( sendto( sock, ( const char * )&newData, data_size, 0,
		( struct sockaddr * )&server_addr, sizeof( server_addr ) ) != data_size )
			SocketError( "Unable to send data." );

	data_size = sizeof( server_addr );
	if( ( recv_data_size = recvfrom( sock, ( char * )&newData, 255, 0,
		( struct sockaddr * )&server_addr, &data_size ) ) < 0 )
			SocketError( "Unable to receive data." );

	if( newData == PACKET_STAT_CONN_ACC )
		std::cout << "Successful connection established with server." << std::endl;
	else if( newData == PACKET_STAT_CONN_EXI )
		SocketError( "Connection already exists on the server.\nExiting." );
}

void client_socket::send_player_data( player_data *data )
{
	net_data game_data( data );
	data_size = sizeof( game_data );
	if( sendto( sock, ( const char * )&game_data, data_size, 0,
		( struct sockaddr * )&server_addr, sizeof( server_addr ) ) != data_size )
			SocketError( "Unable to send game data." );
}
