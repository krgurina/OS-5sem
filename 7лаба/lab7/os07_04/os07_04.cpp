#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;

#define SECOND 10000000

using namespace std;

void main() {
    
    int firsttime = clock();

    HANDLE htimer;
    HANDLE htimer2;

    DWORD pid = GetCurrentProcessId();
    cout << "pid: " << pid << endl;

    htimer = CreateWaitableTimer(NULL, FALSE, L"atimer1");
    htimer2 = CreateWaitableTimer(NULL, FALSE, L"atimer2");

    long long time1 = -60 * SECOND;
    long long time2 = -120 * SECOND;

    if (!SetWaitableTimer(htimer, (LARGE_INTEGER*)&time1, 0, NULL, NULL, FALSE)) throw "Err SetWaitableTimer1";
    if (!SetWaitableTimer(htimer2, (LARGE_INTEGER*)&time2, 0, NULL, NULL, FALSE)) throw "Err SetWaitableTimer2";

    std::cout << "Start timers" << std::endl;

    LPCWSTR an = L"E:\\уник\\ОС\\7лаба\\lab7\\x64\\Debug\\os07_04_X.exe";
    STARTUPINFO si1;
    STARTUPINFO si2;
    PROCESS_INFORMATION pi1;
    PROCESS_INFORMATION pi2;

    ZeroMemory(&si1, sizeof(STARTUPINFO));
    ZeroMemory(&si2, sizeof(STARTUPINFO));

    si1.cb = sizeof(STARTUPINFO);
    si2.cb = sizeof(STARTUPINFO);

    wchar_t cLine1[] = L"E:\\уник\\ОС\\7лаба\\lab7\\x64\\Debug\\os07_04_X.exe 1";
    wchar_t cLine2[] = L"E:\\уник\\ОС\\7лаба\\lab7\\x64\\Debug\\os07_04_X.exe 2";

    if (CreateProcess(an, cLine1, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1))
        cout << "Child Process created" << endl;
    else
        cout << "Child Process not created" << endl;

    if (CreateProcessW(an, cLine2, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2))
        cout << "Child Process created" << endl;
    else
        cout << "Child Process not created" << endl;


    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);
    CloseHandle(pi1.hProcess);
    CloseHandle(pi2.hProcess);
    CloseHandle(htimer);
    CloseHandle(htimer2);

    cout << "time:" << clock() - firsttime <<endl;
    system("pause");
}