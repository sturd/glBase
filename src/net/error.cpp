#include "error.h"

void SocketError( std::string error_msg, int error = 0 )
{
	std::cout << "Error: " << error_msg << std::endl;
	std::cout << "Terminating..." << std::endl;
	exit( error );
}

void SocketError( std::string error_msg )
{
	std::cout << "Error: " << error_msg << std::endl;
	std::cout << "Terminating..." << std::endl;
	exit( 0 );
}
