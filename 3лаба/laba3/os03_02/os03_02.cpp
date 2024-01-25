#include <iostream>
#include<Windows.h>
#include <process.h>
using namespace std;
int main()
{
    LPCWSTR chp1 = L"E:\\уник\\ОС\\3лаба\\laba3\\Debug\\os03_02_1.exe";
    LPCWSTR chp2 = L"E:\\уник\\ОС\\3лаба\\laba3\\Debug\\os03_02_2.exe";
    
    STARTUPINFO w1;
    STARTUPINFO w2;
    
    PROCESS_INFORMATION pi1;
    PROCESS_INFORMATION pi2;
   
    ZeroMemory(&w1, sizeof(STARTUPINFO)); w1.cb = sizeof(STARTUPINFO);
    ZeroMemory(&w2, sizeof(STARTUPINFO)); w2.cb = sizeof(STARTUPINFO);

    if (CreateProcess(chp1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &w1, &pi1))
        cout << "-- Process os03_02_1 created" << endl;
    else {
        cout << "-- Process os03_02_1 not created" << endl;
    }

    if (CreateProcess(chp2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &w2, &pi2))
        cout << "-- Process os03_02_2 created" << endl;
    else {
        cout << "-- Process os03_02_2 not created" << endl;
    }

    for (int i = 0; i < 100; i++) {
        cout << i << "  os03_02 " << " PID:" << _getpid() << endl;;
        Sleep(1000);
    }


    WaitForSingleObject(
        pi1.hProcess, 
        INFINITE      
    );
    WaitForSingleObject(pi2.hProcess, INFINITE); 
    CloseHandle(pi1.hProcess); 
    CloseHandle(pi2.hProcess);
}