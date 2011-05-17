
#include "../../main.h"
#include "data.h"
#include "error.h"

class client_socket
{
	int					sock;			// Local socket descriptor
	unsigned short		listen_port;
	struct sockaddr_in	server_addr;	// Server address
	struct sockaddr_in	recv_addr;		// Address of packet sender

	char		       *ip;				// Server IP address
	char				buffer[ 256 ];
	
#ifdef WIN32
	int					data_size;
#else
	socklen_t			data_size;
#endif

public:
						client_socket( unsigned int port, const char *ip );
					   ~client_socket();

	void				Send();
};
