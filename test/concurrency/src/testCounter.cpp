#include        <iostream>
#include        "Mutex.hh"
#include        "Thread.hh"

static void*    testCounterIncr(void * counter)
{
    Mutex       mutex;

    mutex.lock();
    *(long int *)counter += 2;
    *(long int *)counter += 2;
    *(long int *)counter += 2;
    mutex.unlock();
    return (NULL);
}

void     testCounter()
{
    Thread      threadTestCounter;
    Thread      threadTestCounter2;
    long int    counter = 0;

    threadTestCounter.runTask(testCounterIncr, &counter);
    threadTestCounter2.runTask(testCounterIncr, &counter);
    threadTestCounter.runTask(testCounterIncr, &counter);
    threadTestCounter2.runTask(testCounterIncr, &counter);

    threadTestCounter.join();
    threadTestCounter2.join();

    std::cout << "Counter Value: " << counter << std::endl;

}