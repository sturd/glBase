#include "socket_core.h"

socket_core::socket_core( int sock_mode, const char *addr = DEFAULT_IP, unsigned short port = 1987 )
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
		core_cnt = new client_socket( port, addr );
}

socket_core::~socket_core()
{
	delete core_srv;
	delete core_cnt;
	WSACleanup();
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