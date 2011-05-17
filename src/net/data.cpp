#include "data.h"

net_data::net_data()
{
	packet_status = PACKET_STAT_CONN_BLN;
}

net_data::net_data( short status )
{
	set_status( status );
}

/*
	operator == - Allows quick boolean statement in checking
				  the intent of the received packet.
 */
bool net_data::operator==( const short &status )const
{
	return ( packet_status == status );
}

/*
	set_status() - Allow externals to change the status of
				   the packet in order to request different
				   material from the client/server
 */
void net_data::set_status( short status )
{
	packet_status = status;
}
