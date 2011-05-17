#pragma once

#include <math.h>
#include <stdio.h>

#ifdef WIN32
	#include <winsock2.h>
#else
	#include <sys/socket.h>
	#include <arpa/inet.h>
#endif
#include <string.h>

#include <Windows.h>
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


