/* player_data.h - Data set describing player data to be transferred
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 *
 * player_data.h is the legal property of its developer.
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

#pragma once

class player_data
{
protected:
	int				_Height;
	int				_Width;

	int				_FrameCount;
	int				_CurrentFrame;

	int				_X;
	int				_Y;
	int				_xVel;
	int				_yVel;
	float			_Angle;
	float			_AngVel;

	bool			_Reversed;
	bool			_Paused;
	short			_id;

public:
					player_data();
	player_data	   &operator=( const player_data & );

	void			SetPlayerData( player_data * );
	int				GetWidth();
	int				GetHeight();
	int				GetFrameCount();
	int				GetCurrentFrame();
	int				GetXPos();
	int				GetYPos();
	int				GetXVel();
	int				GetYVel();
	float			GetAngle();
	bool			IsReversed();
	bool			IsPaused();
	short			GetID();
};
