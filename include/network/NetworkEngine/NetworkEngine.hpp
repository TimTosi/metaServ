//
// Server.hpp for Server in /home/tosi_t//Prog/R-Type/Network/inc/General/Server
// 
// Made by timothee tosi
// Login   <tosi_t@epitech.net>
// 
// Started on  Thu Oct 31 14:04:57 2013 timothee tosi
// Last update Sun Nov 24 22:42:10 2013 jonathan hubner
//

#ifndef			NETWORKENGINE_HPP_
# define		NETWORKENGINE_HPP_

# include		<array>
# include		"NetworkDefines.hh"
# include		"NetworkEnginePolicies.hpp"
# include		"RTypeApp.h"

template <typename InitPolicy, typename RunPolicy, typename AcceptPolicy,
	typename DeletePolicy, typename RecvPolicy, typename SendPolicy,
	typename CheckSocketPolicy, typename App, typename MainSocket,
	typename OtherSocket>
class			NetworkEngine :
	private InitPolicy,
	private RunPolicy,
	private AcceptPolicy,
	private DeletePolicy,
	private RecvPolicy,
	private SendPolicy,
	private CheckSocketPolicy
{
	using			InitPolicy::initNetwork;
	using			RunPolicy::runNetwork;
	using			RunPolicy::selectReturn1_;
	using			AcceptPolicy::checkForNewClient;
	using			AcceptPolicy::fdMax_;
	using			DeletePolicy::deleteClient;
	using			RecvPolicy::getMessage;
	using			RecvPolicy::getUdpMessage;
	using			SendPolicy::sendMessage;
	using			SendPolicy::sendUdpMessage;
	using			CheckSocketPolicy::checkSocket;
	using			CheckSocketPolicy::getClientByAddr;

private:
	MainSocket &		mainSocket_;
	OtherSocket &		otherSocket_;
	App &			app_;
	std::array<fd_set, 3>	fdSetsMaster_;
	std::vector<Client>	clientList_;

public:
	NetworkEngine(MainSocket & socket, OtherSocket & otherSocket, App & app)
		: mainSocket_(socket), otherSocket_(otherSocket), app_(app)
	{
	  initNetwork(&mainSocket_, fdSetsMaster_, fdMax_, &otherSocket, clientList_);
	}

  ~NetworkEngine()
	{
	}


  bool			pendingConnection(bool& newClt)
  {
    NetworkEvent *	event;
    if (FD_ISSET(mainSocket_.getHandle(), &(fdSetsMaster_[0])))
      {
	if (!checkForNewClient(mainSocket_, fdSetsMaster_, clientList_))
	  return (false);
	event = new NetworkEvent(Events::CLIENT_CONNECTION);
	event->_infos.clientId = clientList_.back().socket_->getHandle();
	app_.pushNetworkEvent(event);
	newClt = true;
      }
    return (true);
  }

  template <typename Client>
  void			disconnectClient(Client & client)
  {
    NetworkEvent *	event;

    deleteClient(client->socket_->getHandle(), fdSetsMaster_, clientList_);
    event = new NetworkEvent(Events::CLIENT_DISCONNECTION);
    event->_infos.clientId = client->socket_->getHandle();
    app_.pushNetworkEvent(event);
  }

  template <typename Client, typename Packet>
  void			serverToClientTCP(Client & client, Packet & packet)
  {
    if (checkSocket(client, fdSetsMaster_[1])
	&& !sendMessage(client->socket_, *packet))
      {
	disconnectClient(client);
      }
  }

  template <typename Client, typename Packet>
  void			serverToClientUDP(Client & client, Packet & packet)
  {
    if (FD_ISSET(otherSocket_.getHandle(), &(fdSetsMaster_[1])) &&
	!sendUdpMessage(otherSocket_, *packet))
      {
	disconnectClient(client);
      }
  }

  template <typename Client, typename Packet>
  void			clientToServerTCP(Client & client, Packet & packet)
  {
    if (checkSocket(client, fdSetsMaster_[0]) && !getMessage(client->socket_, packet))
      {
	disconnectClient(client);
      }
    else
      app_.pushAPacket(*packet);
  }

  template <typename Packet>
  void			clientToServerUDP(Packet & packet)
  {
    if (FD_ISSET(otherSocket_.getHandle(), &(fdSetsMaster_[0])))
      {
	getUdpMessage(otherSocket_, *packet);
	app_.pushAPacket(*packet);
      }
  }


  void			networkSend(void)
  {
    Client *		client;
    APacket *		packet;

    while ((packet = app_.getNextPacket()) != NULL)
      {
		if ((client = getClientByAddr(reinterpret_cast<RTypeEventInfos *>(packet->getData())->clientId, clientList_)) != nullptr)
	  {
		if (packet->getType() == APacket::TCP)
		{
			serverToClientTCP(client, packet);
		}
	    else
	      serverToClientUDP(client, packet);
	  }
		delete packet;
      }
  }

  void			networkReceive(void)
  {
    static APacket	*packet = new Packet<RTypeEvent>(APacket::INBOUND, APacket::TCP);

    for (auto it = std::begin(clientList_); it != std::end(clientList_); ++it)
      {
		clientToServerTCP(it, packet);
		packet->clear();
		clientToServerUDP(packet);
		packet->clear();
	}
  }

  void			isClient(void)
  {
    NetworkEvent *	event;

    event = new NetworkEvent(Events::CLIENT_CONNECTION);
    event->_infos.clientId = mainSocket_.getHandle();
    app_.pushNetworkEvent(event);
  }

  bool			run(const bool serverMod)
  {
    bool	newClt = false;
    if (!serverMod)
      isClient();
    while (1)
      {
	if (!app_.work() && !serverMod)
	  return (true);
	if (!runNetwork(fdSetsMaster_, clientList_, mainSocket_.getHandle(), fdMax_,
			otherSocket_.getHandle()))
	  return (false);
	if (selectReturn1_ > 0)
	  {
	    if (serverMod == true)
	      {
		newClt = false;
		if (!pendingConnection(newClt))
		  return (false);
		if (newClt)
		  continue;
	      }
	    networkSend();
	    networkReceive();
	  }
      }
    return (true);
  }
};

#endif			// !NETWORKENGINE_HPP_
