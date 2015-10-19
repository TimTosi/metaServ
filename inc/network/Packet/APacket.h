/*
** APacket.h for APacket.h in /home/tosi_t//Prog/R-Type/r-type/include/network/Packet
** 
** Made by Guillaume Rybak
** Login   <rybak_g@epitech.net>
** 
** Started on  Tue Nov 12 17:57:15 2013 guillaume rybak
** Last update Tue Nov 12 22:10:54 2013 timothee tosi
*/

#pragma	once

#ifdef _WIN32
# include "WSNetwork.hh"
#else
# include "UXNetwork.hh"
#endif
#include "IEvent.h"

#define	PACKET_SIZE	512

class				APacket
{
public:
	enum Direction { INBOUND, OUTBOUND };
	enum Type { UNKNOWN, TCP, UDP };

protected:
	enum APacket::Direction	_direction;
	enum APacket::Type	_type;
	sockaddr_in		_addr;
	sockaddr_in *		_addrPtr;
	char			_data[PACKET_SIZE];
	char *			_dataPtr;
	unsigned int		_size;

public:
	APacket(enum APacket::Direction, enum APacket::Type = UNKNOWN);
	APacket(APacket const&);
	APacket const& operator=(APacket const& other);
	virtual ~APacket();

	unsigned int	getSize(void) const;
	sockaddr *		getAddr(void) const;
	sockaddr_in *		getAddrIn(void) const;
	char *			getData(void) const;
	enum APacket::Direction	getDirection(void) const; // WAS CONST
	enum APacket::Type	getType(void) const; // WAS CONST
	void				setType(const enum APacket::Type);
	void				clear(void);
	virtual APacket const &		operator<<(IEvent &event) = 0;
	virtual APacket const &		operator>>(IEvent &event) = 0;
};
