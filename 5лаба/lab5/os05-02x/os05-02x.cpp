#include <Windows.h>
#include <iostream>
void printProcessPrty(HANDLE h)
{
    DWORD prty = GetPriorityClass(h);
    std::cout << " ----- Current PID = " << GetCurrentProcessId() << " \n";
    switch (prty)
    {
        case IDLE_PRIORITY_CLASS:           std::cout << " ----+ priority = IDLE_PRIORITY_CLASS \n"; break;
        case BELOW_NORMAL_PRIORITY_CLASS:   std::cout << " ----+ priority = BELOW_NORMAL_PRIORITY_CLASS \n"; break;
        case NORMAL_PRIORITY_CLASS:         std::cout << " ----+ priority = NORMAL_PRIORITY_CLASS \n"; break;
        case ABOVE_NORMAL_PRIORITY_CLASS:   std::cout << " ----+ priority = ABOVE_NORMAL_PRIORITY_CLASS \n"; break;
        case HIGH_PRIORITY_CLASS:           std::cout << " ----+ priority = HIGH_PRIORITY_CLASS \n"; break;
        case REALTIME_PRIORITY_CLASS:       std::cout << " ----+ priority = REALTIME_PRIORITY_CLASS \n"; break;
        default:                            std::cout << " ----+ priority = ? \n"; break;
    }
    return;
}

void printThreadPrty(HANDLE h)
{
    DWORD icpu = SetThreadIdealProcessor(h, MAXIMUM_PROCESSORS);
    DWORD prty = GetThreadPriority(h);
    std::cout << " ---- Current Thread ID = " << GetCurrentThreadId() << "\n";
    std::cout << " ----+ Processor = " << icpu << " \n";
    std::cout << " ----+ priority = " << prty << " \n";
    
    return;
}

void printCycle(HANDLE ph, HANDLE th, const char name[20])
{
    for (int i = 0; i < 1000000; i++)
    {
        if (i % 1000 == 0)
        {
            std::cout << name << ": Iteration = " << i << "\n";
            printProcessPrty(ph);
            printThreadPrty(th);
            std::cout << "\n\n";
            Sleep(200);
        }
    }
    return;
}

int main()
{
    HANDLE ph = GetCurrentProcess();
    HANDLE th = GetCurrentThread();
    printCycle(ph, th, "Process1");
    system("pause");
}