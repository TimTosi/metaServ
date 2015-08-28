//
// NetworkEngineDefines.hh for NetworkEngineDefines in /home/tosi_t//Prog/R-Type/Network/inc/General/Server
// 
// Made by timothee tosi
// Login   <tosi_t@epitech.net>
// 
// Started on  Sat Nov  9 00:22:03 2013 timothee tosi
// Last update Sun Nov 24 05:49:48 2013 timothee tosi
//

#ifndef					NETWORKENGINEDEFINES_HH_
# define				NETWORKENGINEDEFINES_HH_

# include <sys/types.h>
# ifndef _WIN32
#  include <sys/select.h>
# endif
# include "Socket.hpp"

struct					Client
{
	TcpIPV4StreamNoFlagBlockingSocket	*socket_;
	bool					active_;
	struct sockaddr				clientAddr_;
};

#endif					// !NETWORKENGINEDEFINES_HH_
