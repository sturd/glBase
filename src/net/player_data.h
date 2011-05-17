#pragma once

class player_data
{
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

public:
					player_data( const player_data & );
	player_data	   &operator=( const player_data & );

	
};