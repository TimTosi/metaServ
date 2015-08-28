//
// NetworkPolicies.hpp for NetworkPolicies in /home/tosi_t//Prog/C++/BomberMan/Network/Tests/BombermanNetwork/inc
// 
// Made by timothee tosi
// Login   <tosi_t@epitech.net>
// 
// Started on  Thu May 16 22:28:45 2013 timothee tosi
// Last update Sun Nov 17 04:56:06 2013 timothee tosi
//

#ifndef WSNETWORKPOLICIES_HPP_
# define WSNETWORKPOLICIES_HPP_

# include <iostream>
# include <string>
# include "WSNetwork.hh"
# include "Packet.hpp"



/* -------------------------- PROTOCOL POLICIES ----------------------------- */



class			ProtocolUdpPolicy
{
protected:
	SOCKET		handle_;

protected:
	template <typename Domain>
	bool			initSocket(const Domain domain)
	{
		PROTOENT *	protoStruct;

		if ((protoStruct = getprotobyname("UDP")) == nullptr)
			return (false);
		if ((handle_ = WSASocket(domain, SOCK_DGRAM, protoStruct->p_proto, nullptr, 0, 0)) == INVALID_SOCKET)
			return (false);
		return (true);
	}

	SOCKET		getHandle(void) const
	{
		return (handle_);
	}

	int			getConnection(void) const
	{
		return (SOCK_DGRAM);
	}
};



class			ProtocolTcpPolicy
{
protected:
	SOCKET				handle_;

protected:
	template <typename Domain>
	bool					initSocket(const Domain domain)
	{
		struct protoent *	protoStruct;

		if ((protoStruct = getprotobyname("TCP")) == nullptr)
			return (false);
		if ((handle_ = WSASocket(domain, SOCK_STREAM, protoStruct->p_proto, nullptr, 0, 0)) == INVALID_SOCKET)
			return (false);
		return (true);
	}

	SOCKET		getHandle(void) const
	{
		return (handle_);
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
	bool					bindSocket(const SOCKET handle_, const u_short port)
	{
		struct sockaddr_in	socketBinding;

		socketBinding.sin_family = AF_INET;
		if ((WSAHtons(handle_, port, &socketBinding.sin_port)) == SOCKET_ERROR)
			return (false);
		socketBinding.sin_addr.s_addr = INADDR_ANY;
		if (bind(handle_, reinterpret_cast<const struct sockaddr *>(&socketBinding), sizeof(socketBinding)) == SOCKET_ERROR)
			return (false);
		return (true);
	}

	bool					connectSocket(const SOCKET handle_, const u_short port, const char * serverIp)
	{
		struct sockaddr_in	socketConnecting;

		socketConnecting.sin_family = AF_INET;
		if ((WSAHtons(handle_, port, &socketConnecting.sin_port)) == SOCKET_ERROR)
			return (false);
		socketConnecting.sin_addr.s_addr = inet_addr(serverIp);
		if ((WSAConnect(handle_, reinterpret_cast<const struct sockaddr *>(&socketConnecting), sizeof(socketConnecting), nullptr, nullptr, nullptr, nullptr)) == SOCKET_ERROR)
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
	bool		bindSocket(const SOCKET handle_, const u_short port)
	{
		struct sockaddr_in6	socketBinding;

		socketBinding.sin6_family = AF_INET6;
		if (WSAHtons(handle_, port, nullptr) == INVALID_SOCKET)
			return (false);
		socketBinding.sin6_addr = in6addr_any;
		if (bind(handle_, reinterpret_cast<const struct sockaddr *>(&socketBinding), sizeof(socketBinding)) == SOCKET_ERROR)
			return (false);
		return (true);
	}

	bool		connectSocket(const SOCKET handle_, const u_short port, const char * serverIp)
	{
		return (false);
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
	bool			sendPacket(const SOCKET handle_, APacket & packet) const
	{
		DWORD		bytesSent;
		WSABUF		buff;

		buff.buf = packet.getData();
		buff.len = packet.getSize();
		return (((WSASend(handle_, &buff, 1, &bytesSent, 0, nullptr, nullptr)) != SOCKET_ERROR));
	}

	bool			receivePacket(const SOCKET handle_, APacket & packet) const
	{
		DWORD		bytesRecv;
		WSABUF		buff;
		DWORD		flags;

		flags = 0;
		buff.buf = packet.getData();
		buff.len = packet.getSize();
		if (WSARecv(handle_, &buff, 1, &bytesRecv, &flags, nullptr, nullptr) == 0)
			return (true);
		return (false);
	}
};



class			ConnectionDatagramPolicy
{
protected:
	bool			sendPacket(const SOCKET handle_, APacket & packet) const
	{
		DWORD		bytesSent;
		WSABUF	buff;

		buff.buf = packet.getData();
		buff.len = packet.getSize();
		return (((WSASendTo(handle_, &buff, 1, &bytesSent, 0, packet.getAddr(), sizeof(sockaddr_in), nullptr, nullptr)) != SOCKET_ERROR));
	}

	bool				receivePacket(const SOCKET handle_, APacket & packet) const
	{
		socklen_t		len = sizeof(sockaddr);
		WSABUF			buff;
		DWORD			BytesRecv = 0;
		DWORD			Flags = 0;

		buff.buf = packet.getData();
		buff.len = packet.getSize();
		return ((WSARecvFrom(handle_, &buff, 1, &BytesRecv, &Flags, packet.getAddr(), &len, nullptr, nullptr)) != SOCKET_ERROR);
	}
};


/* --------------------------- ACCEPT POLICIES ------------------------------- */



class			NoFlagAcceptPolicy
{
protected:
	int				acceptSocket(int handle_, sockaddr & newSocket)
	{
		socklen_t	socketStructSize = sizeof(newSocket);
		unsigned int	fdHandle_;
		
		if ((fdHandle_ = WSAAccept(handle_, &newSocket, &socketStructSize, NULL, NULL)) == INVALID_SOCKET)
		  return (-1);
		return (fdHandle_);
	}
};



/* --------------------------- BLOCKING POLICIES ------------------------------- */



class			BlockingModPolicy
{
protected:
	bool			setBlockingMod(const SOCKET)
	{
		return (true);
	}
};


class			NonBlockingModPolicy
{
protected:
	bool			setBlockingMod(const SOCKET handle_)
	{
		return (true);
	}
};

#endif			// !WSNETWORKPOLICIES_HPP_
