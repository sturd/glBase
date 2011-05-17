/* data.cpp - Network data code, describes data formatting when transferring
 *			  over network.
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * data.cpp is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

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
