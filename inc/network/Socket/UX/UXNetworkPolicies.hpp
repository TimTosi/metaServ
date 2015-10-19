#ifndef			UXNETWORKPOLICIES_HPP_
# define		UXNETWORKPOLICIES_HPP_

# include		<iostream>
# include		<string>

# include		"UXNetwork.hh"
# include		"Packet.hpp"



/* -------------------------- PROTOCOL POLICIES ----------------------------- */



class			ProtocolUdpPolicy
{
protected:
  int			handle_;

protected:
  template <typename Domain>
  bool			initSocket(const Domain domain)
  {
    struct protoent *	protoStruct;

    if ((protoStruct = getprotobyname("UDP")) == nullptr)
      return (false);
    if ((handle_ = socket(domain, SOCK_DGRAM, protoStruct->p_proto)) == -1)
      return (false);
    return (true);
  }

  int			getConnection(void) const
  {
    return (SOCK_DGRAM);
  }
};



class			ProtocolTcpPolicy
{
protected:
  int			handle_;

protected:
  template <typename Domain>
  bool			initSocket(const Domain domain)
  {
    struct protoent *	protoStruct;

    if ((protoStruct = getprotobyname("TCP")) == nullptr)
      return (false);
    if ((handle_ = socket(domain, SOCK_STREAM, protoStruct->p_proto)) == -1)
      return (false);
    return (true);
  }

  int			getConnection(void) const
  {
    return (SOCK_STREAM);
  }
};



/* -------------------------------- DOMAIN POLICIES ------------------------------ */



class			DomainIPV4Policy
{
protected:
  bool			bindSocket(const int handle_, const int port)
  {
    struct sockaddr_in	socketBinding;

    socketBinding.sin_family = AF_INET;
    socketBinding.sin_port = htons(port);
    socketBinding.sin_addr.s_addr = INADDR_ANY;
    if (bind(handle_, reinterpret_cast<const struct sockaddr *>(&socketBinding),
	     sizeof(socketBinding)) == -1)
      return (false);
    return (true);
  }

  bool			connectSocket(const int handle_, const int port,
				      const char * serverIp)
  {
    struct sockaddr_in	socketConnecting;

    socketConnecting.sin_family = AF_INET;
    socketConnecting.sin_port = htons(port);
    socketConnecting.sin_addr.s_addr = inet_addr(serverIp);
    if ((connect(handle_, reinterpret_cast<const struct sockaddr *>(&socketConnecting),
		 sizeof(socketConnecting))) == -1)
      return (false);
    return (true);
  }

  int			getDomain() const
  {
    return (AF_INET);
  }
};



class			DomainIPV6Policy
{
protected:
  bool			bindSocket(const int handle_, const int port)
  {
    struct sockaddr_in6	socketBinding;

    socketBinding.sin6_family = AF_INET6;
    socketBinding.sin6_port = htons(port);
    socketBinding.sin6_addr = in6addr_any;
    if (bind(handle_, reinterpret_cast<const struct sockaddr *>(&socketBinding),
	     sizeof(socketBinding)) == -1)
      return (false);
    return (true);
  }

  bool			connectSocket(const int handle_, const int port,
				      const char * serverIp)
  {
    // DO STUFF
    (void)handle_;
    (void)port;
    (void)serverIp;
    return (true);
  }

  int			getDomain() const
  {
    return (AF_INET6);
  }
};



/* -------------------------- CONNECTION POLICIES --------------------------- */



class			ConnectionStreamPolicy
{
protected:
  bool			sendPacket(const int handle_, APacket & packet) const
  {
    if ((send(handle_, packet.getData(), packet.getSize(), 0)) != packet.getSize())
      return (false);
    return (true);
  }

  bool			receivePacket(const int handle_, APacket & packet) const
  {
    if ((recv(handle_, packet.getData(), packet.getSize(), 0)) < 1)
      return (false);
    return (true);
  }
};



class			ConnectionDatagramPolicy
{
protected:
  bool			sendPacket(const int handle_, APacket & packet) const
  {
    if ((sendto(handle_, packet.getData(), packet.getSize(), 0,
		packet.getAddr(), sizeof(sockaddr_in))) != packet.getSize())
      return (false);
    return (true);
  }

  bool			receivePacket(const int handle_, APacket & packet) const
  {
    socklen_t		size = sizeof(sockaddr);

    if ((recvfrom(handle_, packet.getData(), packet.getSize(), 0,
		  packet.getAddr(), &size)) == -1)
      return (false);
    return (true);
  }
};



/* --------------------------- ACCEPT POLICIES ------------------------------- */



class			NoFlagAcceptPolicy
{
protected:
  int			acceptSocket(int handle_, sockaddr & newSocket)
  {
    socklen_t		socketStructSize = sizeof(newSocket);

    return (accept(handle_, &newSocket, &socketStructSize));
  }
};



/* --------------------------- BLOCKING POLICIES ------------------------------- */



class			BlockingModPolicy
{
protected:
  bool			setBlockingMod(const int)
  {
    return (true);
  }
};


class			NonBlockingModPolicy
{
protected:
  bool			setBlockingMod(const int handle_)
  {
    if ((fcntl(handle_, F_SETFL, O_NONBLOCK, 0)) == -1)
      return (false);
    return (true);
  }
};

#endif			// !UXNETWORKPOLICIES_HPP_
