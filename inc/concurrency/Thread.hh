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

MEMBER FUNC
http://stackoverflow.com/questions/16503184/generic-thread-c-wrapper-function-for-c

PATTERN
http://accu.org/index.php/journals/562

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


    /* void * runTask(T (*func)(void)) also works */
    template<typename T>
    void        runTask(T (*func)(void))
    {
        pthread_create(&_thread, NULL, (void *(*)(void *))func, NULL);
    }

    template<typename T, typename U, typename V>
	void *		runTask(T (*func)(U), V arg)
    {
        pthread_create(&_thread, NULL, (void *(*)(void *))func, (void *)arg);
        return (NULL);
    }
};

#endif			/* !THREAD_HH_ */