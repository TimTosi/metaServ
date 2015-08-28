//
// client.cpp for main in /home/tosi_t//Prog/C++/BomberMan/Network/Tests/BombermanNetwork/src
// 
// Made by timothee tosi
// Login   <tosi_t@epitech.net>
// 
// Started on  Wed May 22 19:42:36 2013 timothee tosi
// Last update Thu Nov 21 23:53:27 2013 timothee tosi
//

#include		<cstdlib>
#include		"NetworkEngine.hpp"
#include		"RTypeApp.h"

int			strToInt(char *str)
{
  if (str == NULL)
    std::cout << "NO ARG WILL CAUSE SEGFAULT" << std::endl;
  return (std::atoi(str));
}

int			main(int, char **av)
{
  RTypeApp		app;
  TcpIPV4StreamNoFlagBlockingSocket    	toto(strToInt(av[1]), "127.0.0.1", 7070);
  UdpIPV4DatagramNoFlagBlockingSocket   titi(strToInt(av[1]) + 1);
  NetworkEngine<RTypeInitPolicy,
		RTypeRunPolicy,
		RTypeAcceptPolicy,
		RTypeDeletePolicy,
		RTypeRecvPolicy,
		RTypeSendPolicy,
		RTypeCheckSocketPolicy,
		RTypeApp,
		TcpIPV4StreamNoFlagBlockingSocket,
		UdpIPV4DatagramNoFlagBlockingSocket>	client(toto, titi, app);

  client.run(false);
  return (true);
}
