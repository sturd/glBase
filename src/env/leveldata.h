/* Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://sturd.co.uk/
 *
 * leveldata.h is the legal property of its developer.
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
#include "../net/socket_core.h"

#include "../sprite/sprite.h"
#include "player.h"

#include "../input/input_handler.h"

#define SECT_MAX 	80
#define LVL_PTH 	"image/level1/level.cfg"
#define DAT_PTH 	"image/level1/img.cfg"

class LevelData
{
	socket_core	   *net_core;

	input_handler  *inputs;
	input_init_data init_device;

	short			player_count;
	player		   *player_sprite[ 6 ];

public:
					LevelData( init_sock_dat * );
	void			LoadData();
	void			Execute();
};
