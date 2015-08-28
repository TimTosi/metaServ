//
//
//
//
//
//

#pragma once

# include	<cstring>
# include	"APacket.h"

template<typename _EVENT_>
class Packet : public APacket
{
public:
	Packet(enum APacket::Direction dir,	enum APacket::Type type = APacket::UNKNOWN) : APacket(dir, type) {}
	Packet(const APacket& other) : APacket(other.getDirection(), other.getType())
	{
		std::memcpy(_dataPtr, other.getData(), other.getSize());
	}

	virtual ~Packet() {}

	APacket const& operator<<(IEvent &event)
	{
		_EVENT_	&e = static_cast<_EVENT_ &>(event);

		std::memcpy(_dataPtr, &(e._infos), e.getSize());
		return (*this);
	}

	APacket const& operator>>(IEvent &event)
	{
		_EVENT_	&e = static_cast<_EVENT_ &>(event);

		std::memcpy(&(e._infos), _dataPtr, e.getSize());
		return (*this);
	}
};
