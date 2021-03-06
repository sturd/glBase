/* Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 *
 * sprite.cpp is the legal property of its developer.
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

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

#include "sprite.h"

sprite::sprite( void )
{
	_Reversed = false;
	_Paused = false;
	_X = _Y = _xVel = _yVel = 0;
}

sprite::sprite( const char *texture, int xPos, int yPos, int frames, short local_id )
: player_data()
{
	TGAImg image;
	image.Load( ( char * )texture, frames );
	_X = xPos;
	_Y = yPos;
	_id = local_id;

	SetSprite( image );
}

sprite::sprite( char *ID, char *Path, int xPos, int yPos )
: player_data()
{
	SetPosition( xPos, yPos );
	LoadConfig( ID, Path );
}

sprite::~sprite( void )
{
	DeleteFrames();
}

void sprite::DeleteFrames()
{
	// Delete sprite frames from graphics memory
	for( int scan = 0; scan < _FrameCount; ++scan )
		glDeleteTextures( 1, &_tex_id[ scan ] );
}

void sprite::SetPosition( int xPos, int yPos )
{
	_X = xPos;
	_Y = yPos;
}

void sprite::SetFrameCount( int FrmCnt )
{
	_FrameCount = FrmCnt;
}

void sprite::SetSprite( TGAImg &Img )
{
	// Clear current attributes of sprite
	DeleteFrames();
	_CurrentFrame = 0;
	_FrameCount = Img.GetFrameCount();
	_Height = Img.GetHeight();
	_Width = Img.GetWidth() / _FrameCount;

	if( _FrameCount > 1 )
	{
		// declare container for individual frames
		// (10 frames max)
		TGAImg *temp[ 10 ];

		for( int init = 0; init < _FrameCount; ++init )
		{
			temp[ init ] = 
				new TGAImg( Img.GetWidth(), Img.GetHeight(), Img.GetBPP() );

			// Execute function to isolate frame
			temp[ init ]->SetImg( Img.GetFrame( init ) );
		}

		for( int scan = 0; scan < _FrameCount; ++scan )
		{
			// Have OpenGL generate a texture object handle
			glGenTextures( 1, &_tex_id[ scan ] );
		 
			// Bind the texture object
			glBindTexture( GL_TEXTURE_2D, _tex_id[ scan ] );
		 
			// Set the texture's stretching properties
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

			// Export images to GPU
			glTexImage2D( GL_TEXTURE_2D, 0, Img.GetBPP(), _Width, _Height, 0, 
						  GL_RGBA, GL_UNSIGNED_BYTE, temp[ scan ]->GetImg()  );
		}
	}
	else
	{
		glGenTextures( 1, &_tex_id[ 0 ] );
		glBindTexture( GL_TEXTURE_2D, _tex_id[ 0 ] );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexImage2D( GL_TEXTURE_2D, 0, Img.GetBPP(), _Width, _Height, 0, 
					  GL_RGBA, GL_UNSIGNED_BYTE, Img.GetImg()  );
	}
}

// Convert integer value of pixel to floating
// point value of OpenGL X coordinate
float sprite::pixToGLXCoord( int Pixel )
{
	float pixRatio = ( 2.0f / ( float )WIDTH );
	return pixRatio * ( float )Pixel - 1.0f;
}

// Convert integer value of pixel to floating
// point value of OpenGL Y coordinate
float sprite::pixToGLYCoord( int Pixel )
{	Pixel = HEIGHT - Pixel - _Height;
	float pixRatio = ( 2.0f / ( float )HEIGHT );
	return pixRatio * ( float )Pixel - 1.0f;
}

int sprite::glXCoordToPix( float Coord )
{
	return 0;
}

int sprite::glYCoordToPix( float Coord )
{
	return 0;
}

void sprite::DrawImage( void )
{

	if( _CurrentFrame == _FrameCount )
		_CurrentFrame = 0;

	//glLoadIdentity();

	float W_RATIO = ( ( float )_Width / WIDTH ) * 2;
	float H_RATIO = ( ( float )_Height / HEIGHT ) * 2;

	// Update positions based upon velocities...
	_X += _xVel;
	_Y += _yVel;
	
	// Add/subtract angular velocity to/from the current angle
	_Angle += _AngVel;

	if( _Angle > 360 )
		_Angle -= 360;

	float glX = pixToGLXCoord( _X );
	float glY = pixToGLYCoord( _Y );
	
	// Calculate mid-points of sprite for a central rotation
	float glMidX = pixToGLXCoord( _X + ( _Width  / 2 ) );
	float glMidY = pixToGLYCoord( _Y + ( _Height / 2 ) - _Height );

	glPushMatrix();
	glTranslatef( glMidX, glMidY, 0.0f );
		glRotatef( _Angle, 0.0f, 0.0f, 1.0f );
	glTranslatef( -glMidX, -glMidY, 0.0f );

	glTranslatef( glX, glY, 0.0f );

	//glBindTexture( GL_TEXTURE_2D, _tex_id[ _CurrentFrame ] );

	//glEnable( GL_BLEND );
	//glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glBegin( GL_QUADS );
		if( _Reversed )
		{
			// Display texture reversed on screen
			glTexCoord2f( -1.0f, 1.0f );		glVertex2f( W_RATIO,	0.0f	);	// Top left ( BTMR )
			glTexCoord2f(  0.0f, 1.0f );		glVertex2f( 0.0f,		0.0f	);	// Bottom left
			glTexCoord2f(  0.0f, 0.0f );		glVertex2f( 0.0f,		H_RATIO );	// Bottom Right
			glTexCoord2f( -1.0f, 0.0f );		glVertex2f( W_RATIO,	H_RATIO );	// Top right
		}
		else
		{
			glTexCoord2f( 1.0f, 1.0f );		glVertex2f( W_RATIO,	0.0f	);	// Top left ( BTMR )
			glTexCoord2f( 0.0f, 1.0f );		glVertex2f( 0.0f,		0.0f	);	// Bottom left
			glTexCoord2f( 0.0f, 0.0f );		glVertex2f( 0.0f,		H_RATIO );	// Bottom Right
			glTexCoord2f( 1.0f, 0.0f );		glVertex2f( W_RATIO,	H_RATIO );	// Top right
		}
	glEnd();
	glPopMatrix();

	if( !_Paused )
		++_CurrentFrame;
}

// Function to load sprite from file
// To be deleted and replaced with binary file I/O at some point
void sprite::LoadConfig( char *SpriteID, char *ConfPath )
{
	// Declaration of config data set
	char ID[ MAX_LENGTH ] = "";
	char Path[ MAX_LENGTH ] = "";
	int Frames = 0;

	// Flag to match ID string
	bool Match = true;

	// Load config file
	ifstream config( ConfPath, ios::in );

	// Terminate program if config file
	// cannot be opened
	if( !config )
	{
		// Provide user feedback of error
		// before program terminates
		cout << "Unable to find sprite data: " << SpriteID << endl;
	}

	// Scan file from start to finish
	while( !config.eof() )
	{
		// Reset match flag to true
		Match = true;

		// Load values from file
		config >> ID >> Path >> Frames;


		// Scan the SpriteID to check for a match
		for( int ChrScan = 0; ChrScan < sizeof( SpriteID ); ++ChrScan )
		{
			if( ID[ ChrScan ] != SpriteID[ ChrScan ] )
			{
				// If mismatch found, set flag
				// to false and break from loop
				Match = false;
				break;
			}
		}

		// If Match flag still true
		// store data to object
		if( Match )
		{
			_FrameCount = Frames;

			TGAImg image;
			image.Load( Path, _FrameCount );

			SetSprite( image );
			break;
		}
	}
	config.close();
}

// Routine to get velocity along X-Axis
int sprite::GetXVel( void )
{
	return _xVel;
}

int sprite::GetYVel( void )
{
	return _yVel;
}

// Routine to return angular velocity
float sprite::GetAngVel()
{
	return _AngVel;
}

// Routine to set velocity along X-Axis
void sprite::SetXVel( int Vel )
{
	_xVel = Vel;
}

void sprite::SetYVel( int Vel )
{
	_yVel = Vel;
}

// Routine to set angular velocity
void sprite::SetAngVel( float Vel )
{
	_AngVel = Vel;
}

// Routine to cause image to flip in horizontal direction
void sprite::Reverse()
{
	// XOR operation, toggles true and false
	_Reversed ^= true;
}

// Routine to cause sprite animation to pause
void sprite::TogglePause( void )
{
	// XOR operation, toggles true and false
	_Paused ^= true;
}

// Routine to rotate sprite to specified angle
void sprite::Rotate( float Angle )
{
	_Angle = Angle;
}

/*void sprite::set_player_data( player_data *data )
{
	_Height =		data->get_height();
	_Width  =		data->get_width();
	_FrameCount =	data->get_frame_count();
	_CurrentFrame = data->get_current_frame();
	_X =			data->get_x();
	_Y =			data->get_y();
	_xVel =			data->get_x_vel();
	_yVel =			data->get_y_vel();
	_Angle =		data->get_angle();
	_Reversed =		data->is_reversed();
	_Paused =		data->is_paused();
	_id =			data->get_id();
}*/

player_data *sprite::get_player_data()
{
	return ( player_data * )this;
}
