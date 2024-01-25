#include <iostream>
#include <Windows.h>

using namespace std;
DWORD pId = NULL;
CRITICAL_SECTION cs;

DWORD WINAPI ChildThreadFirst()
{
	DWORD tId = GetCurrentThreadId();

	for (int i = 0; i < 90; i++)
	{
		if (i == 30)
		{
			EnterCriticalSection(&cs);
		}

		cout << "Thread A: " << "PID = " << pId << "tId = " << tId << ": " << i << endl;

		if (i == 60)
		{
			LeaveCriticalSection(&cs);
		}
		Sleep(100);

	}
	cout << "\n------------------  Thread A finished  ------------------\n";

	return 0;
}

DWORD WINAPI ChildThreadSecond()
{
	DWORD tId = GetCurrentThreadId();

	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
		{
			EnterCriticalSection(&cs);
		}

		cout << "Thread B: " << "PID = " << pId << "tId = " << tId << ": " << i << endl;

		if (i == 60)
		{
			LeaveCriticalSection(&cs);
		}

		Sleep(100);

	}

	cout << "\n------------------  Thread B finished  ------------------\n";

	return 0;
}

int main()
{
	pId = GetCurrentProcessId();
	DWORD tId = GetCurrentThreadId();
	DWORD childIdFirst = NULL;
	DWORD childIdSecond = NULL;

	HANDLE hChildFirst = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThreadFirst, NULL, 0, &childIdFirst);
	HANDLE hChildSecond = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThreadSecond, NULL, 0, &childIdSecond);

	InitializeCriticalSection(&cs);

	for (int i = 0; i < 90; i++)
	{

		if (i == 30)
		{
			EnterCriticalSection(&cs);
		}

		cout << "Main: " << "PID = " << pId << "tId = " << tId << ": " << i << endl;

		if (i == 60)
		{
			LeaveCriticalSection(&cs);;
		}

		Sleep(100);
	}

	cout << "\n------------------  Main finished  ------------------\n";

	WaitForSingleObject(hChildFirst, INFINITE);
	WaitForSingleObject(hChildSecond, INFINITE);

	DeleteCriticalSection(&cs);

	CloseHandle(hChildFirst);
	CloseHandle(hChildSecond);

	system("pause");
	return 0;
}

