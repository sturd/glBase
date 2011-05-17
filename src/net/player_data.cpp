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