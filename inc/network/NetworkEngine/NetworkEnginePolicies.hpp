//
// ServerPolicies.hpp for ServerPolicies in /home/tosi_t//Prog/R-Type/Network/inc/General/Server
// 
// Made by timothee tosi
// Login   <tosi_t@epitech.net>
// 
// Started on  Sat Nov  2 14:40:42 2013 timothee tosi
// Last update Sun Nov 24 22:41:43 2013 jonathan hubner
//

#ifndef			NETWORKENGINEPOLICIES_HPP_
# define		NETWORKENGINEPOLICIES_HPP_

# include		<algorithm>
# include		<vector>
# include		<cstring>
# include		"NetworkEngineDefines.hh"
# include		"RTypeEvent.h"



// ------------------------------------------ INIT POLICIES ------------------------------------------



class			RTypeInitPolicy
{
protected:
  template <typename Socket, typename FDSets, typename Socket2, typename ClientList>
  bool			initNetwork(Socket handle_, FDSets & fdSetsMaster_, int & fdMax_,
#ifdef _SERVER
				    Socket2 handle2_, ClientList & /*clientList_*/)
#else
				    Socket2 handle2_, ClientList & clientList_)
#endif
  {
    FD_ZERO(&(fdSetsMaster_[0]));
    FD_ZERO(&(fdSetsMaster_[1]));
    FD_SET(handle_->getHandle(), &(fdSetsMaster_[0]));
    if (handle_->getHandle() > handle2_->getHandle())
      fdMax_ = handle_->getHandle();
    else
      fdMax_ = handle2_->getHandle();
#ifndef _SERVER
    Client		newClient;
    newClient.socket_ = &(*handle_);
    newClient.active_ = true;
    clientList_.push_back(newClient);
#endif
    return (true);
  }
};



// ------------------------------------------ ACCEPT POLICIES ------------------------------------------



class			RTypeAcceptPolicy
{
protected:
  int			fdMax_;

protected:
  template <typename Socket, typename FDSets, typename ClientList>
  bool					checkForNewClient(Socket & handle_, FDSets & fdSetsMaster_,
							  ClientList & clientList_)
  {
    if (FD_ISSET(handle_.getHandle(), &(fdSetsMaster_[0])) &&
	!acceptNewClient(handle_, fdSetsMaster_, clientList_))
      return (false);
    return (true);
  }

  template <typename Socket, typename FDSets, typename ClientList>
  bool					acceptNewClient(Socket & handle_, FDSets & fdSetsMaster_,
							ClientList & clientList_)
  {
    int					fd;
    Client				newClient;
    TcpIPV4StreamNoFlagBlockingSocket *	newSocket = new TcpIPV4StreamNoFlagBlockingSocket;

    if ((fd = handle_.accepting(newClient.clientAddr_)) == -1)
      {
	delete newSocket;
	return (false);
      }
    newClient.socket_ = newSocket;
    newClient.socket_->setHandle(fd);
    newClient.active_ = true;
    FD_SET(fd, &(fdSetsMaster_[0]));
    FD_SET(fd, &(fdSetsMaster_[1]));
    clientList_.push_back(newClient);
    setMaxFd(fd, 0, clientList_);
    return (true);
  }

  template <typename ClientList>
  void					setMaxFd(int fdMax, int mod, ClientList & clientList_)
  {
    if ((fdMax > fdMax_) && (mod == 0))
      fdMax_ = fdMax;
    else if (mod == 1)
      {
	fdMax_ = -1;
	for (auto it = std::begin(clientList_); it != std::end(clientList_); ++it)
	  {
	    if (it->socket_->getHandle() > fdMax_)
	      fdMax_ = it->socket_->getHandle();
	  }
      }
  }
  
};



// ------------------------------------------ DELETE POLICIES -----------------------------------------



class			RTypeDeletePolicy
{
protected:
	template <typename FDSets, typename ClientList>
	bool			deleteClient(const int fd, FDSets & fdSetsMaster_, ClientList & clientList_)
	{
	  FD_CLR(fd, &(fdSetsMaster_[0]));
	  FD_CLR(fd, &(fdSetsMaster_[1]));
	  for (auto it = std::begin(clientList_); it != std::end(clientList_); ++it)
	    {
	      if (it->socket_->getHandle() == fd)
		{
		  it->active_ = false;
		  return (true);
		}
	    }
	  return (false);
	}
};



// -------------------------------------- CHECK SOCKET POLICIES ---------------------------------------



class			RTypeCheckSocketPolicy
{
protected:
	template <typename Handler, typename FDSets>
	bool			checkSocket(Handler & handler_, FDSets & fdSets_)
	{
		if ((handler_->active_ == true) && (FD_ISSET(handler_->socket_->getHandle(), &(fdSets_))))
			return (true);
		return (false);
	}

	template <typename ClientList>
	Client *		getClientByAddr(int id, ClientList & clientList_)
	{
		for (auto it = std::begin(clientList_); it != std::end(clientList_); ++it)
		{
		  if (it->socket_->getHandle() == id)
		    return (&(*it));
		}
		return (nullptr);
	}
};



// ------------------------------------------ RUN POLICIES ------------------------------------------



class			RTypeRunPolicy
{
protected:
	int			selectReturn1_;

protected:
	template <typename FDSets, typename ClientList>
	bool			runNetwork(FDSets & fdSetsMaster_, ClientList & clientList_,
		int listenerHandle_, int & fdMax_, int otherHandle_)
	{
		struct timeval	tv = {0, 50000};

		setFdSets(listenerHandle_, fdSetsMaster_, clientList_, otherHandle_);
		if ((selectReturn1_ = select(fdMax_ + 1, &(fdSetsMaster_[0]), &(fdSetsMaster_[1]), NULL, &tv)) == -1)
		  return (false);
		return (true);
	}

	template <typename FDSets, typename ClientList>
	void				setFdSets(int listenerHandle_, FDSets & fdSetsMaster_, ClientList & clientList_, int otherHandle_)
	{
		selectReturn1_ = 0;
		FD_ZERO(&(fdSetsMaster_[0]));
		FD_ZERO(&(fdSetsMaster_[1]));
		FD_SET(listenerHandle_, &(fdSetsMaster_[0]));
		FD_SET(otherHandle_, &(fdSetsMaster_[0]));
		FD_SET(otherHandle_, &(fdSetsMaster_[1]));
		for (auto it = std::begin(clientList_); it != std::end(clientList_); ++it)
		{
			FD_SET(it->socket_->getHandle(), &(fdSetsMaster_[0]));
			FD_SET(it->socket_->getHandle(), &(fdSetsMaster_[1]));
		}
	}
};



// ------------------------------------------ SEND POLICIES ------------------------------------------



class			RTypeSendPolicy
{
protected:
	template <typename Socket, typename Packet>
	bool			sendMessage(Socket & socket, Packet & packet)
	{
		if (!socket->sending(packet))
			return (false);
		return (true);
	}

	template <typename Socket, typename Packet>
	bool			sendUdpMessage(Socket & socket, Packet & packet)
	{
		if (!socket.sending(packet))
			return (false);
		return (true);
	}
};



// ----------------------------------------- RECEIVE POLICIES -----------------------------------------

class			RTypeRecvPolicy
{
protected:
	template <typename Socket, typename Packet>
	bool			getMessage(Socket & socket, Packet & packet)
	{
		if (!socket->receiving(*packet))
		  return (false);
		//std::cout << packet->getData() << std::endl;
		return (true);
	}

	template <typename Socket, typename Packet>
	bool			getUdpMessage(Socket & socket, Packet & packet)
	{
		if (!socket.receiving(packet))
			return (false);
		//std::cout << packet.getData() << std::endl;
		return (true);
	}
};



#endif			// !NETWORKENGINEPOLICIES_HPP_
