#ifndef					MUTHEX_HH_
# define				MUTHEX_HH_

#include				<pthread.h>


/*
	CHECK ERRORS ON INIT AND DESTROY

	MASSE MAN PAGES !!!!
	https://computing.llnl.gov/tutorials/pthreads/
*/

class 					Mutex
{
private:
	pthread_mutex_t		_mutex;

public:
	Mutex();
	~Mutex();
    int                 lock(void);
    int                 unlock(void);
    int                 trylock(void);
};

#endif					/* !MUTHEX_HH_ */