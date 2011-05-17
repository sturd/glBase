##----------------------------------------------------------------------------
# Created with genmake.pl v1.1 on Tue May 17 13:43:58 2011
# genmake.pl home: http://muquit.com/muquit/software/
# Copryright: GNU GPL (http://www.gnu.org/copyleft/gpl.html)
##----------------------------------------------------------------------------
rm=/bin/rm -f
CC= cc
DEFS=  
PROGNAME= test
INCLUDES=  -I.
LIBS= -lGL -lSDL -lSDL_mixer -lboost_thread


DEFINES= $(INCLUDES) $(DEFS) -DSYS_UNIX=1
CFLAGS= -g $(DEFINES)

SRCS = src/net/error.cpp src/net/data.cpp src/net/client_list.cpp src/net/server_sock.cpp src/net/client_sock.cpp src/net/socket_core.cpp src/sprite/tga.cpp src/sprite/sprite.cpp src/env/leveldata.cpp main.cpp

OBJS = src/net/error.o src/net/data.o src/net/client_list.o src/net/server_sock.o src/net/client_sock.o src/net/socket_core.o src/sprite/tga.o src/sprite/sprite.o src/env/leveldata.o main.o

.c.o:
	$(rm) $@
	$(CC) $(CFLAGS) -c $*.c

all: $(PROGNAME)

$(PROGNAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGNAME) $(OBJS) $(LIBS)

clean:
	$(rm) $(OBJS) $(PROGNAME) core *~
