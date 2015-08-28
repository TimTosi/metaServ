//
// APacket.cpp for APacket in /
// 
// Made by timothee tosi
// Login   <tosi_t@epitech.net>
// 
// Started on  Tue May 21 21:21:38 2013 timothee tosi
// Last update Tue Nov 12 22:12:33 2013 timothee tosi
//

#include <cstring>
#include		"APacket.h"

APacket::APacket(enum APacket::Direction dir, enum APacket::Type type)
:	_direction(dir),
	_type(type),
	_addrPtr(&_addr),
	_dataPtr(_data),
	_size(PACKET_SIZE)
{
	this->clear();
}

APacket::APacket(APacket const& other)
:	_direction(other.getDirection()),
	_type(other.getType()),
	_addrPtr(&_addr),
	_dataPtr(_data),
	_size(PACKET_SIZE)
{
	std::memcpy(_dataPtr, other.getData(), sizeof(_data));
	std::memcpy(_addrPtr, other.getAddr(), sizeof(_addr));
}

APacket::~APacket()
{
}

APacket const&	APacket::operator=(APacket const& other)
{
	std::memcpy(_dataPtr, other.getData(), sizeof(_data));
	std::memcpy(_addrPtr, other.getAddr(), sizeof(_addr));
	return (*this);
}

sockaddr		*APacket::getAddr(void) const
{
	return (reinterpret_cast<sockaddr *>(_addrPtr));
}

sockaddr_in		*APacket::getAddrIn(void) const
{
	return (_addrPtr);
}

char			*APacket::getData(void) const
{
	return (_dataPtr);
}

unsigned	APacket::getSize(void) const //WAS CONST
{
	return (_size);
}

void		APacket::clear(void)
{
	std::memset(_dataPtr, 0, sizeof(_data));
	std::memset(_addrPtr, 0, sizeof(_addr));
}

enum APacket::Direction	APacket::getDirection(void)	const //WAS CONST
{
	return (_direction);
}
enum APacket::Type		APacket::getType(void) const //WAS CONST
{
	return (_type);
}
