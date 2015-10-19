#include        <iostream>
#include        <assert.h>

#include        "Thread.hh"

#include        "testTaskRun.hh"
#include        "DummyClass.hh"


static void     testTaskRun1(void)
{
    std::cout << "This is a Task executed with signature void func(void)." << std::endl;
}

static int      testTaskRun2(void)
{
    std::cout << "This is a Task executed with signature int func(void)." << std::endl;
    return (1);
}

static void     testTaskRun3(int &nb)
{
    std::cout << "This is a Task executed with signature void func(int &)." << std::endl;
    assert(nb == TEST_DEFINE);
}

static int      testTaskRun4(int &nb)
{

    std::cout << "This is a Task executed with signature int func(int &)." << std::endl;
    assert(nb == TEST_DEFINE);
    return (nb);
}

void            testTask(void)
{
    Thread          threadTask;
    int             nb = TEST_DEFINE;

    threadTask.runTask(testTaskRun1);
    threadTask.runTask(testTaskRun2);
    threadTask.runTask(testTaskRun3, &nb);
    threadTask.runTask(testTaskRun4, &nb);
}