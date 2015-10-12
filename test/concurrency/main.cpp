#include		<iostream>
#include		<cstdlib>
#include		<unistd.h>
#include		"Mutex.hh"
#include		"Thread.hh"

static void*	testTaskRun(void * arg)
{
	(void)arg;
	std::cout << "This is a Task Executed!\n";

	return (NULL);
}

static void		testTask(void)
{
	Thread		threadTestTask(testTaskRun, NULL);
}

static void*	testCounterIncr(void * counter)
{
	Mutex		mutex;

	mutex.lock();
	*(long int *)counter += 2;
	*(long int *)counter += 2;
	*(long int *)counter += 2;
	mutex.unlock();
	return (NULL);
}

static void		testCounter()
{
	Thread		threadTestCounter;
	Thread		threadTestCounter2;
	long int	counter = 0;

	threadTestCounter.runTask(testCounterIncr, (void*)&counter);
	threadTestCounter2.runTask(testCounterIncr, (void*)&counter);
	threadTestCounter.runTask(testCounterIncr, (void*)&counter);
	threadTestCounter2.runTask(testCounterIncr, (void*)&counter);

	threadTestCounter.join();
	threadTestCounter2.join();

	std::cout << "Counter Value: " << counter << std::endl;

}

int				main()
{
	testTask();
	testCounter();
	return (EXIT_SUCCESS);
}