// Filename:	plyrchr.cpp
// Author:		Craig Sturdy
// Version:		0.1
// Date:		04/12/2008

#pragma once

#include "plyrchr.h"

PlyrChr::PlyrChr(){}

PlyrChr::PlyrChr( char *PlyrSprite, int FrameCount ) : sprite()
{
	_Direction = UP;
	LoadConfig( CHR_UP, CHR_CFG );
	SetPosition( 100, 100 );
	TogglePause();
}

PlyrChr::PlyrChr( int xPos, int yPos ) : sprite()
{
	_Direction = UP;
	LoadConfig( CHR_UP, CHR_CFG );
	SetPosition( xPos, yPos );
	TogglePause();
}

void PlyrChr::Run( int Dir )
{
	if( _Paused )
		TogglePause();

	switch( Dir )
	{
		case RIGHT:
			if( _Direction != RIGHT )
			{
				_Direction = RIGHT;
				LoadConfig( CHR_RT, CHR_CFG );
			}
			SetXVel( 10 );
			break;

		case LEFT:
			if( _Direction != LEFT )
			{
				_Direction = LEFT;
				LoadConfig( CHR_LF, CHR_CFG );
			}
			SetXVel( -10 );
			break;

		case UP:
			if( _Direction != UP )
			{
				_Direction = UP;
				LoadConfig( CHR_UP, CHR_CFG );
			}
			SetYVel( 10 );
			break;

		case DOWN:
			if( _Direction != DOWN )
			{
				_Direction = DOWN;
				LoadConfig( CHR_DN, CHR_CFG );
			}
			SetYVel( -10 );
			break;

		default:
			break;
	}
}

void PlyrChr::Stop()
{
	if( !_Paused )
		TogglePause();

	SetXVel( 0 );
	SetYVel( 0 );
}

int PlyrChr::GetXPos( void )
{
	return _X;
}

int PlyrChr::GetYPos( void )
{
	return _Y;
}

int PlyrChr::GetHeight( void )
{
	return _Height;
}

int PlyrChr::GetWidth( void )
{
	return _Width;
}
