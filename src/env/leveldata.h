#pragma once
#include "../../main.h"
#include "../sprite/sprite.h"
#include "../net/socket_core.h"

#define SECT_MAX 	80
#define LVL_PTH 	"image/level1/level.cfg"
#define DAT_PTH 	"image/level1/img.cfg"

class LevelData
{
	socket_core	   *net_core;
					//LevelData();
	bool			key_right_down;
	bool			key_left_down;
	bool			key_up_down;
	bool			key_down_down;
	
	sprite		   *sonic;

public:
					LevelData( int );
	void			LoadData();
	void			Execute();
};
