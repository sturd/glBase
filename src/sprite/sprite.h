/* Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * sprite.h is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#pragma once

#include "../../main.h"
#include "../net/player_data.h"
#include "tga.h"

class sprite
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

	bool			_Reversed;
	bool			_Paused;

	GLuint			_tex_id[ 10 ];
	void			DeleteFrames();
	void			SetPosition( int, int );
	void			SetFrameCount( int );
	void			SetSprite( TGAImg & );

	float			pixToGLXCoord( int );
	float			pixToGLYCoord( int );
	int				glXCoordToPix( float );
	int				glYCoordToPix( float );

public:
					sprite( void );
					sprite( const char *, int, int, int );
					sprite( char *, char *, int, int );
					sprite( char * );
				   ~sprite( void );

   	//std::string		get_player_data();
	int				GetXVel( void );
	int				GetYVel( void );

	void			SetXVel( int );
	void			SetYVel( int );

	void			LoadConfig( char *, char * );
	void			DrawImage( void );
	void			Reverse( void );
	void			TogglePause( void );
	void			Rotate( float );
	
	player_data	   *get_player_data();
};
