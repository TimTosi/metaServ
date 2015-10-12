#ifndef			THREAD_HH_
# define		THREAD_HH_

#include		<pthread.h>

/* TO CHECK
pthread_attr_setdetachstate
pthread_self
pthread_sigmask
pthread_getcpuclockid
pthread_cleanup_push

http://man7.org/linux/man-pages/man3/pthread_attr_init.3.html
http://linux.die.net/man/3/pthread_create

book C++ Concurrency in Action

http://progsch.net/wordpress/?p=81
http://stackoverflow.com/questions/28669311/c-how-to-implement-thread-pool-for-tasks-when-each-worker-thread-has-to-do-fe
*/

class 			Thread
{
private:
	pthread_t	_thread;
   	int			_state;

public:
	Thread();
	Thread(void *(*func)(void *), void * arg);
	~Thread();
	void		join(void);
	void *		runTask(void *(*func)(void *));
	void *		runTask(void *(*func)(void *), void * arg);
};

#endif			/* !THREAD_HH_ */