#include <iostream>

#include "server_sock.h"
#include "client_sock.h"

int main( int argc, char *argv[] )
{
	const unsigned int port = 1987;
	server_socket *srv = 0;
	client_socket *cnt = 0;

#ifdef WIN32
	/**
		Init Winsock service
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
        return 1;
    }
#endif

	if( !argv[ 1 ] )
		SocketError( "No arguments found." );

	else if( !strcmp( argv[ 1 ], "--server" ) )
		srv = new server_socket( port );

	else if( !strcmp( argv[ 1 ], "--client" ) )
	{
		if( !argv[ 2 ] )
			SocketError( "Invalid arguments for client mode." );

		cnt = new client_socket( port, argv[ 2 ] );
	}

	else
		SocketError( "Invalid arguments found." );

	if( cnt != 0 )
		cnt->Send();

	else if( srv != 0 )
	{
		std::cout << "Greetings from THREAD_MAIN!" << std::endl;
		while( !srv->is_done() ){}
	}

	delete srv;
	delete cnt;

	return 0;
}
