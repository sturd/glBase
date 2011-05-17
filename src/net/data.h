#include <string>
#pragma once

#define PACKET_STAT_CONN_BLN 0x00	// Blank packet set by default constructor
#define PACKET_STAT_CONN_NEW 0x01	// Packet requesting new connection
#define PACKET_STAT_CONN_DIE 0x02	// Packet requesting disconnect
#define PACKET_STAT_CONN_ACC 0x03	// Packet accepting connection
#define PACKET_STAT_CONN_EXI 0x04	// Connection already open

class net_data
{
	short					packet_status;	// Packet status header

public:
							net_data();
							net_data( short );

	bool 					operator==( const short &status )const;

	void					set_status( short );
};
