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
		std::cout << "Connection already exists with server." << std::endl;
}
