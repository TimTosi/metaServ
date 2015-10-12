#include        "Mutex.hh"

Mutex::Mutex()
{
	pthread_mutex_init(&_mutex, NULL);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&_mutex);
}

int             Mutex::lock(void)
{
    return (pthread_mutex_lock(&_mutex));
}

int             Mutex::unlock(void)
{
    return (pthread_mutex_unlock(&_mutex));
}

int             Mutex::trylock(void)
{
    return (pthread_mutex_trylock(&_mutex));
}