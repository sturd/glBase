#pragma once
#include <iostream>

#include "server_sock.h"
#include "client_sock.h"

#define SOCKET_SERVER	0x01
#define SOCKET_CLIENT	0x02
#define DEFAULT_IP		"127.0.0.1"

class socket_core
{

	int					mode_;
	server_socket	   *core_srv;	// Core server descriptor
	client_socket	   *core_cnt;	// Core socket descriptor

#ifdef WIN32
	void				init_ws2();
#endif

public:
						socket_core( int, const char *, unsigned short );
					   ~socket_core();
};