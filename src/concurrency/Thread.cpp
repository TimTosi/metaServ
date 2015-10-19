#include	"Thread.hh"

Thread::Thread()
{

}

Thread::Thread(void *(*func)(void *), void *arg)
{
	pthread_create(&_thread, NULL, func, arg);
}

Thread::~Thread()
{
	pthread_join(_thread, NULL);
}

void		Thread::join(void)
{
	pthread_join(_thread, NULL);
}
