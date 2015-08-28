//
// NetworkDefines.hh for NetworkDefines in /home/tosi_t//Prog/C++/BomberMan/Network/Tests/BombermanNetwork/inc
// 
// Made by timothee tosi
// Login   <tosi_t@epitech.net>
// 
// Started on  Fri May 17 02:51:13 2013 timothee tosi
// Last update Sat Nov  9 04:11:42 2013 timothee tosi
//

#ifndef			NETWORK_DEFINES_HH_
# define		NETWORK_DEFINES_HH_

# include		"Socket.hpp"

typedef Socket<ProtocolTcpPolicy, DomainIPV4Policy, ConnectionDatagramPolicy, NoFlagAcceptPolicy, BlockingModPolicy>	TcpIPV4DatagramNoFlagBlockingSocket;
typedef Socket<ProtocolTcpPolicy, DomainIPV4Policy, ConnectionDatagramPolicy, NoFlagAcceptPolicy, NonBlockingModPolicy>	TcpIPV4DatagramNoFlagNonBlockingSocket;
typedef Socket<ProtocolTcpPolicy, DomainIPV4Policy, ConnectionStreamPolicy, NoFlagAcceptPolicy, BlockingModPolicy>	TcpIPV4StreamNoFlagBlockingSocket;
typedef Socket<ProtocolTcpPolicy, DomainIPV4Policy, ConnectionStreamPolicy, NoFlagAcceptPolicy, NonBlockingModPolicy>	TcpIPV4StreamNoFlagNonBlockingSocket;
typedef Socket<ProtocolTcpPolicy, DomainIPV6Policy, ConnectionDatagramPolicy, NoFlagAcceptPolicy, BlockingModPolicy>	TcpIPV6DatagramNoFlagBlockingSocket;
typedef Socket<ProtocolTcpPolicy, DomainIPV6Policy, ConnectionDatagramPolicy, NoFlagAcceptPolicy, NonBlockingModPolicy>	TcpIPV6DatagramNoFlagNonBlockingSocket;
typedef Socket<ProtocolTcpPolicy, DomainIPV6Policy, ConnectionStreamPolicy, NoFlagAcceptPolicy, BlockingModPolicy>	TcpIPV6StreamNoFlagBlockingSocket;
typedef Socket<ProtocolTcpPolicy, DomainIPV6Policy, ConnectionStreamPolicy, NoFlagAcceptPolicy, NonBlockingModPolicy>	TcpIPV6StreamNoFlagNonBlockingSocket;


typedef Socket<ProtocolUdpPolicy, DomainIPV4Policy, ConnectionDatagramPolicy, NoFlagAcceptPolicy, BlockingModPolicy>	UdpIPV4DatagramNoFlagBlockingSocket;
typedef Socket<ProtocolUdpPolicy, DomainIPV4Policy, ConnectionDatagramPolicy, NoFlagAcceptPolicy, NonBlockingModPolicy>	UdpIPV4DatagramNoFlagNonBlockingSocket;
typedef Socket<ProtocolUdpPolicy, DomainIPV4Policy, ConnectionStreamPolicy, NoFlagAcceptPolicy, BlockingModPolicy>	UdpIPV4StreamNoFlagBlockingSocket;
typedef Socket<ProtocolUdpPolicy, DomainIPV4Policy, ConnectionStreamPolicy, NoFlagAcceptPolicy, NonBlockingModPolicy>	UdpIPV4StreamNoFlagNonBlockingSocket;
typedef Socket<ProtocolUdpPolicy, DomainIPV6Policy, ConnectionDatagramPolicy, NoFlagAcceptPolicy, BlockingModPolicy>	UdpIPV6DatagramNoFlagBlockingSocket;
typedef Socket<ProtocolUdpPolicy, DomainIPV6Policy, ConnectionDatagramPolicy, NoFlagAcceptPolicy, NonBlockingModPolicy>	UdpIPV6DatagramNoFlagNonBlockingSocket;
typedef Socket<ProtocolUdpPolicy, DomainIPV6Policy, ConnectionStreamPolicy, NoFlagAcceptPolicy, BlockingModPolicy>	UdpIPV6StreamNoFlagBlockingSocket;
typedef Socket<ProtocolUdpPolicy, DomainIPV6Policy, ConnectionStreamPolicy, NoFlagAcceptPolicy, NonBlockingModPolicy>	UdpIPV6StreamNoFlagNonBlockingSocket;

#endif			/* !NETWORK_DEFINES_HH_ */
