//
// Socket.hpp for Socket in /home/tosi_t//Prog/C++/BomberMan/Network/Tests/BombermanNetwork/inc
// 
// Made by timothee tosi
// Login   <tosi_t@epitech.net>
// 
// Started on  Wed May 15 22:32:21 2013 timothee tosi
// Last update Sun Nov 24 23:06:30 2013 jonathan hubner
//

#ifndef			SOCKET_HPP_
# define		SOCKET_HPP_

# ifdef			_WIN32
#  include		"WSNetworkPolicies.hpp"
#  include		"WSSocketDebug.hh"
# else
#  include		"UXNetworkPolicies.hpp"
#  include		"UXSocketDebug.hh"
# endif

template <typename ProtocolPolicy, typename DomainPolicy, typename ConnectionPolicy,
	  typename AcceptPolicy, typename BlockingPolicy>
class			Socket :
  private ProtocolPolicy,
  private DomainPolicy,
  private ConnectionPolicy,
  private AcceptPolicy,
  private BlockingPolicy
{
  using			ProtocolPolicy::handle_;
  using			ProtocolPolicy::initSocket;
  using			ProtocolPolicy::getConnection;
  using			DomainPolicy::bindSocket;
  using			DomainPolicy::connectSocket;
  using			DomainPolicy::getDomain;
  using			ConnectionPolicy::sendPacket;
  using			ConnectionPolicy::receivePacket;
  using			AcceptPolicy::acceptSocket;
  using			BlockingPolicy::setBlockingMod;

private:
  const int		port_;
  const int		clientNb_;
  bool			errorHandle_;
  bool			isOpen_;

  Socket(const Socket &) = delete;

public:
  Socket()
    : port_(0), clientNb_(0), errorHandle_(false), isOpen_(false)
  {

  }

  Socket(const int port)
    : port_(port), clientNb_(0), errorHandle_(false), isOpen_(false)
  {
    if (!debugInit(initSocket(getDomain())))
      errorHandle_ = true;
    else
      isOpen_ = true;
    if (!debugBind(bindSocket(handle_, port_)))
      errorHandle_ = true;
    if (!debugSettings(setBlockingMod(handle_)))
      errorHandle_ = true;
  }

  Socket(const int port, const int clientNb)
    : port_(port), clientNb_(clientNb), errorHandle_(false), isOpen_(false)
  {
    if (!debugInit(initSocket(getDomain())))
      errorHandle_ = true;
    else
      isOpen_ = true;
    if (!debugBind(bindSocket(handle_, port_)))
      errorHandle_ = true;
    if (!debugSettings(setBlockingMod(handle_)))
      errorHandle_ = true;
    if (!listening(clientNb))
      errorHandle_ = true;
  }

  Socket(const int port, const std::string & corresIp, const int corresPort)
    : port_(port), clientNb_(0), errorHandle_(false), isOpen_(false)
  {
    if (!debugInit(initSocket(getDomain())))
      {
	errorHandle_ = true;
      }
    else
      isOpen_ = true;
    if (!debugBind(bindSocket(handle_, port_)))
      {
	errorHandle_ = true;
      }
    if (!debugSettings(setBlockingMod(handle_)))
      {
	errorHandle_ = true;
      }
    if (!connecting(corresPort, corresIp.c_str()))
      errorHandle_ = true;
  }

  ~Socket()
  {
    closing();
  }

  bool			sending(APacket & packet)
  {
    if (!debugSend(sendPacket(handle_, packet), packet))
      return (false);
    return (true);
  }

  bool			receiving(APacket & packet)
  {
    if (!receivePacket(handle_, packet))
      return (false);
    return (true);
  }

  bool			connecting(const int port, const char * serverIp)
  {
    if (!debugConnect(connectSocket(handle_, port, serverIp)))
      return (false);
    return (true);
  }

  int			accepting(sockaddr & newSocketFd)
  {
    return (debugAccept(acceptSocket(handle_, newSocketFd)));
  }

  bool			listening(const int clientNb)
  {
    if (!debugListen(listen(handle_, clientNb)))
      return (false);
    return (true);
  }

  void			closing(void)
  {
    if (isOpen_ == true)
#ifdef _WIN32
      closesocket(handle_);
#else
    close(handle_);
#endif
  }

  void			setHandle(const int handle)
  {
    handle_ = handle;
    setOpen(true);
  }

  void			setPort(const int port)
  {
    port_ = port;
  }

  void			setOpen(const bool mod)
  {
    isOpen_ = mod;
  }

  int			getHandle(void) const
  {
    return (handle_);
  }

  int			getPort(void) const
  {
    return (port_);
  }

  bool			getError(void) const
  {
    return (errorHandle_);
  }
};


#endif			// !SOCKET_HPP_
