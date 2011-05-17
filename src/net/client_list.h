#ifdef WIN32
	#include <winsock2.h>
#else
	#include <sys/socket.h>
	#include <arpa/inet.h>
#endif

#include <string.h>
#include <string>

/*
	START COMM STATUS CODES
 */

#define						SCK_STAT_ITEM_EMPTY  0x00
#define						SCK_STAT_INCOME_WAIT 0x01

class client_list
{
	int						stream_stat_;	// Do we listen for her?
	struct sockaddr_in		client_addr_;	// Client socket address

	void					zero_address();	// Purge item address space

public:
							client_list( struct sockaddr_in * );
						   ~client_list();

	bool					operator==( const std::string &addr )const;

	int						get_status();
	void					dc_client();
	std::string				get_ip();
};
