# include       <iostream>
# include       "Thread.hh"


static void     testTaskRun1(void)
{
    std::cout << "This is a Task Executed!\n";
}

static int      testTaskRun2(void)
{
    std::cout << "This is a Task Executed!\n";
    return (1);
}

static void     testTaskRun3(int &nb)
{
    std::cout << "This is "<< nb << " Task Executed!\n";
}

static int      testTaskRun4(int &nb)
{

    std::cout << "This is "<< nb << " Task Executed!\n";
    return (1);
}

void            testTask(void)
{
    Thread          threadTask;
    int             nb = 2;

    threadTask.runTask(testTaskRun1);
    threadTask.runTask(testTaskRun2);
    threadTask.runTask(testTaskRun3, &nb);
    threadTask.runTask(testTaskRun4, &nb);
}