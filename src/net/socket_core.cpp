/* socket_core.cpp - Socket I/O allowing network communication
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * socket_core.cpp is the legal property of its developers, whose names
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

#include "socket_core.h"

socket_core::socket_core( short sock_mode, const char *addr = DEFAULT_IP, unsigned short port = 1987 )
{
	mode_ = sock_mode;

#ifdef WIN32	// Initialise winsock on windows os'
	init_ws2();
#endif

	if( sock_mode == SOCKET_SERVER )
	{
		core_srv = new server_socket( port );
	}
	else
	{
		core_cnt = new client_socket( port, addr );
		core_cnt->Send();
	}	
}

socket_core::~socket_core()
{
	delete core_srv;
	delete core_cnt;
#ifdef WIN32
	WSACleanup();
#endif
}

#ifdef WIN32
void socket_core::init_ws2()
{

	/**
		Winsock initialiser dross
	 */
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

	/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        printf("WSAStartup failed with error: %d\n", err);
        exit( 1 );
    }
}
#endif

short socket_core::mode()
{
	return mode_;
}

player_data socket_core::send_player_data( player_data *data )
{
	player_data tmp_data;
	if( mode_ == SOCKET_CLIENT )
	{
		core_cnt->send_player_data( data );
	}
	else if( mode_ == SOCKET_SERVER )
	{
		core_srv->update_local_player( data );
		tmp_data = core_srv->get_player_data( 0 );
	}
	return tmp_data;
}
