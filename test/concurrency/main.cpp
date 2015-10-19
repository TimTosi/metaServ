#include		<iostream>
#include		<cstdlib>
#include		<unistd.h>
#include		"Mutex.hh"
#include		"Thread.hh"

static void		testTaskRun1(void)
{
	std::cout << "This is a Task Executed!\n";
}

static int		testTaskRun2(void)
{
	std::cout << "This is a Task Executed!\n";
	return (1);
}

static void		testTaskRun3(int &nb)
{
	std::cout << "This is "<< nb << "Task Executed!\n";
}

static int		testTaskRun4(int &nb)
{

	std::cout << "This is "<< nb << "Task Executed!\n";
	return (1);
}

static void		testTask(void)
{
	Thread			threadTask;
	int				nb = 2;

	threadTask.runTask(testTaskRun1);
	threadTask.runTask(testTaskRun2);
	threadTask.runTask(testTaskRun3, &nb);
	threadTask.runTask(testTaskRun4, &nb);
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

	threadTestCounter.runTask(testCounterIncr, &counter);
	threadTestCounter2.runTask(testCounterIncr, &counter);
	threadTestCounter.runTask(testCounterIncr, &counter);
	threadTestCounter2.runTask(testCounterIncr, &counter);

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