#include "client_list.h"

client_list::client_list( struct sockaddr_in *client_addr )
{
	if( client_addr )
	{
		/*
			Client address exists, save a copy locally
			and set list item to open.
		 */
		zero_address();
		client_addr_ = *client_addr;
		stream_stat_ = SCK_STAT_INCOME_WAIT;
	}
	else
		stream_stat_ = SCK_STAT_ITEM_EMPTY;
}

client_list::~client_list()
{
	zero_address();
	stream_stat_ = SCK_STAT_ITEM_EMPTY;
}

void client_list::zero_address()
{
	// Zero out address structure for initialisation
	memset( &client_addr_, 0, sizeof( client_addr_ ) );
}

/*
	== - Determine equality of list item with another
		 item.  Should only be used when establishing
		 new connection with client.
		 Compare string format IP address for time being...
 */
bool client_list::operator==( const std::string &addr )const
{
	return ( addr == std::string( inet_ntoa( client_addr_.sin_addr ) ) );
}

/*
	get_status() - Determine client is connected.  Allows
				   server to pass client object and avoid
				   being blocked by a non-responsive client.
 */
int client_list::get_status()
{
	return stream_stat_;
}

/*
	dc_client() - Delete address structure and set stream
				  to closed to prevent poll blocking.
 */
void client_list::dc_client()
{
	zero_address();
	stream_stat_ = SCK_STAT_ITEM_EMPTY;
}

/*
	get_ip() - Determine IP address of client in order to
			   fire message at their machine.
 */
std::string client_list::get_ip()
{
	return std::string( inet_ntoa( client_addr_.sin_addr ) );
}
