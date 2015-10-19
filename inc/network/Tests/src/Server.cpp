//
// main.cpp for main in /home/tosi_t//Prog/C++/BomberMan/Network/Tests/BombermanNetwork/src
// 
// Made by timothee tosi
// Login   <tosi_t@epitech.net>
// 
// Started on  Wed May 15 22:51:21 2013 timothee tosi
// Last update Thu Nov 21 23:50:29 2013 timothee tosi
//

#include			<unistd.h>
#include			"NetworkEngine.hpp"
#include			"RTypeApp.h"

int				main()
{
  RTypeApp			app;
  UdpIPV4DatagramNoFlagBlockingSocket	titi(7071);
  TcpIPV4StreamNoFlagBlockingSocket	toto(7070, 10);
  NetworkEngine<RTypeInitPolicy,
		RTypeRunPolicy,
		RTypeAcceptPolicy,
		RTypeDeletePolicy,
		RTypeRecvPolicy,
		RTypeSendPolicy,
		RTypeCheckSocketPolicy,
		RTypeApp,
		TcpIPV4StreamNoFlagBlockingSocket,
		UdpIPV4DatagramNoFlagBlockingSocket>	server(toto, titi, app);

  server.run(true);
  return (true);
}
