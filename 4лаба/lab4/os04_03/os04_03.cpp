#include <Windows.h>
#include <iostream>

DWORD pid = NULL;
using namespace std;

DWORD WINAPI ChildThread() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 50; i++)
	{
		cout << i << " " << "os04_02_T1: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
	}

	return 0;
}

DWORD WINAPI ChildSecondThread() {
	DWORD tid = GetCurrentThreadId();
	for (int i = 0; i < 125; i++)
	{
		cout << i << " " << "os04_02_T2: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
		if (i == 124) {
			cout << "Wakeup Parent Thread \n";
			exit(0);
		}
	}

	return 0;
}



int main()
{
	pid = GetCurrentProcessId();

	DWORD tid = GetCurrentThreadId();
	DWORD childId = NULL;
	DWORD childSecondId = NULL;
	HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread, NULL, 0, &childId);
	HANDLE hChildSecond = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildSecondThread, NULL, 0, &childSecondId);

	for (int i = 0; i < 100; i++)
	{
		cout << i << " " << "Parent Thread: " << "PID: " << pid << " " << "TID: " << tid << ";" << endl;
		Sleep(1000);
		if (i == 20) {
			SuspendThread(hChild);
			cout << "\nSuspend os04_02_T1 \n";
		}
		else if (i == 60) {
			ResumeThread(hChild);
			cout << "\nResume os04_02_T1 \n";
		}

		if (i == 40) {
			SuspendThread(hChildSecond);
			cout << "\nSuspend os04_02_T2 \n";
		}
	}
	ResumeThread(hChildSecond);
	cout << "\nResume os04_02_T2 \n";

	WaitForSingleObject(hChild, INFINITE);
	WaitForSingleObject(hChildSecond, INFINITE);
	CloseHandle(hChild);
	CloseHandle(hChildSecond);

}