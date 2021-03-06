# glBase #

This is a small experimental piece of software, using openGL for graphical output and animations.
So far, the program (in server mode) spawns a new thread that executes a basic, non-blocking
UDP server.  This listens out for incoming client requests.


## Requires ##

This software is built upon a couple of supporting libraries that are required in your build system before the software can be compiled.  These libraries are listed below.

---
  - [libsdl](http://www.libsdl.org/)
  - [libsdl_mixer](http://www.libsdl.org/projects/SDL_mixer/)
  - [libboost](http://www.boost.org/) (Until the C++0x spec is finalised)
	
## Meeting Requirements ##

### Ubuntu ###

On Ubuntu, the requirements can be installed with a simple command from the Terminal.
	
	sudo apt-get install build-essential libboost-thread-dev libsdl-mixer1.2-dev
	
The apt package manager will take care of lower dependencies automatically.

## Execution ##

### Server ###

Unix/Linux:

	./test --server

Windows:

	test --server

### Client ###

The client requires a running server in order to communicate.
	
Unix/Linux:

	/test --client TARGET_IPV4_ADDRESS

Windows:

	test --client TARGET_IPV4_ADDRESS
		
An example of the TARGET_IPV4_ADDRESS would be '127.0.0.1' or the address of a remote
computer, if the server is not running on the same machine.

