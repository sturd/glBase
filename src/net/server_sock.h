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

	boost::thread	   *incoming_thread;	// Thread listening for new clients

	int					client_count;		// Number of clients currently connected
	client_list		   *client_addr_lst[ MAX_CLIENTS ];

	bool				is_done_;

	struct sockaddr_in	init_local_address( unsigned short );
	void				send_reply( net_data *, struct sockaddr_in * );


#ifdef WIN32
	SOCKET				sock;
	int					data_size;			// Size of incoming data
	u_long				block_mode;
#else
	int					sock;				// Socket descriptor
	socklen_t           data_size;
#endif
	
	char				buffer[ 255 ];		// Buffer for incoming data...
	int					recv_data_size;		// Size of recieved data

	void				handle_new( net_data *, struct sockaddr_in * );
	void				listen();			// Listen for incoming data
public:
						server_socket( unsigned short port );
					   ~server_socket();

	bool				is_done();
};
