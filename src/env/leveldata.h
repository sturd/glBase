/* Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * leveldata.h is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
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
