/* player_data.cpp - Data set describing player data to be transferred
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * player_data.cpp is the legal property of its developers, whose names
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

#include "player_data.h"

player_data::player_data( const player_data &data ) :
				_Height(		data._Height ),
				_Width(			data._Width ),
				_FrameCount(	data._FrameCount ),
				_CurrentFrame(	data._CurrentFrame ),
				_X(				data._X ),
				_Y(				data._Y ),
				_xVel(			data._xVel ),
				_yVel(			data._yVel ),
				_Angle(			data._Angle ),
				_Reversed(		data._Reversed ),
				_Paused(		data._Paused )
{

}

player_data &player_data::operator=( const player_data &data )
{
	return *this;
}

int player_data::get_height()
{
	return _Height;
}
