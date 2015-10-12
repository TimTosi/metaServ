#ifndef		SCOPEDLOCK_HH_
# define	SCOPEDLOCK_HH_

#include	"Mutex.hh"

class 		ScopedLock
{
private:
	Mutex &	_mutex;
private:
	ScopedLock() = delete;
public:
	ScopedLock(Mutex & mutex);
	~ScopedLock();
};

#endif		/* !SCOPEDLOCK_HH_ */