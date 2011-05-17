/* main.h - Global variables + core included software
 *
 * Copyright (C) 2011 Craig Sturdy
 *
 * Email: craig <at> sturd <dot> co <dot> uk
 * Example Usage: http://www.sturd.co.uk/sonicjs/
 *
 * main.h is the legal property of its developers, whose names
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

#include <math.h>
#include <stdio.h>

#ifdef WIN32
	#include <winsock2.h>
	#include <Windows.h>
#else
	#include <sys/socket.h>
	#include <arpa/inet.h>
#endif
#include <string.h>

#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_opengl.h>

#define WIDTH	 800
#define HEIGHT	 600

#define UP		 0
#define DOWN	 1
#define LEFT	 2
#define RIGHT	 3

// Collision flags
#define COLLECT	0
#define DESTROY	1
#define STOP	2

#define CHR_UP "U"
#define CHR_DN "D"
#define CHR_LF "L"
#define CHR_RT "R"

#define CHR_CFG "image/char/char.cfg"


#define MAX_LENGTH 32

const float PI = 4.0f * atan( 1.0f );


