// Filename:	sprite.h
// Author:		Craig Sturdy
// Version:		0.1
// Date:		04/12/2008

#pragma once

#include "../../main.h"
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

   	std::string		get_player_data();
	int				GetXVel( void );
	int				GetYVel( void );

	void			SetXVel( int );
	void			SetYVel( int );

	void			LoadConfig( char *, char * );
	void			DrawImage( void );
	void			Reverse( void );
	void			TogglePause( void );
	void			Rotate( float );
};
