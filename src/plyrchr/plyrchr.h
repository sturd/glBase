#pragma once

#include "../sprite/tga.h"
#include "../../main.h"

class PlyrChr : public sprite
{
	//TGAImg			_PlyrImg;
	//TGAImg			_Stand;
	int				_Direction;

					PlyrChr();
public:
					PlyrChr( char *, int );
					PlyrChr( int, int );
	void			Run( int );
	void			Stop( void );

	int				GetXPos( void );
	int				GetYPos( void );
	int				GetHeight( void );
	int				GetWidth( void );
};
