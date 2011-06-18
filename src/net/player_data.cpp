/* player_data.cpp - Data set describing player data to be transferred
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * player_data.cpp is the legal property of its developer.
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

player_data::player_data()
{
	_Height = 0;
	_Width = 0;
	_FrameCount = 0;
	_CurrentFrame = 0;
	_X = 0;
	_Y = 0;
	_xVel = 0;
	_yVel = 0;
	_Angle = 0.0f;
	_Reversed = false;
	_Paused = false;
	_id = 0;
}

player_data &player_data::operator=( const player_data &data )
{
	return *this;
}

void player_data::set_player_data( player_data *data )
{
	_Height	=		data->get_height();
	_Width  =		data->get_width();
	_FrameCount =	data->get_frame_count();
	_CurrentFrame =	data->get_current_frame();
	_X =			data->get_x();
	_Y =			data->get_y();
	_xVel =			data->get_x_vel();
	_yVel =			data->get_y_vel();
	_Angle =		data->get_angle();
	_Reversed =		data->is_reversed();
	_Paused =		data->is_paused();
	_id =			data->get_id();
}

int player_data::get_width()
{
	return _Width;
}

int player_data::get_height()
{
	return _Height;
}

int player_data::get_frame_count()
{
	return _FrameCount;
}

int player_data::get_current_frame()
{
	return _CurrentFrame;
}

int player_data::get_x()
{
	return _X;
}

int player_data::get_y()
{
	return _Y;
}

int player_data::get_x_vel()
{
	return _xVel;
}

int player_data::get_y_vel()
{
	return _yVel;
}

float player_data::get_angle()
{
	return _Angle;
}

bool player_data::is_reversed()
{
	return _Reversed;
}

bool player_data::is_paused()
{
	return _Paused;
}

short player_data::get_id()
{
	return _id;
}
