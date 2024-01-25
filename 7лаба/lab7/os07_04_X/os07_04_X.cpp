#include <Windows.h>
#include <iostream>
#include <ctime>
#include <TlHelp32.h>
#include <stdio.h>
using namespace std;

bool stop1 = false;

int GetSimpleNumbers(int n)
{
	for (int i = 2; i <= n / 2; i++)
		if ((n % i) == 0)
			return 0;
	return 1;
}


DWORD ChildThread1()
{
	for (long long i = 2; ; i++)
	{
		if (stop1) break;
		if (GetSimpleNumbers(i))
			cout << i << endl;
	}
	return 0;
}


int main(int argc, char* argv[])
{
	HANDLE htimer = NULL;
	DWORD childId1 = NULL;
	int parm = 1;

	if (argc > 1) parm = atoi(argv[1]);

	if (parm == 1) {
		 htimer = OpenWaitableTimer(TIMER_ALL_ACCESS, FALSE, L"atimer1");
	}
	else {
		 htimer = OpenWaitableTimer(TIMER_ALL_ACCESS, FALSE, L"atimer2");
	}

	clock_t start = clock();

	HANDLE childHandle1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ChildThread1, NULL, 0, &childId1);

	WaitForSingleObject(htimer, INFINITE);
	stop1 = true;
	WaitForSingleObject(childHandle1, INFINITE);


	CloseHandle(htimer);

	CloseHandle(childHandle1);

	cout << "Time = " << (clock() - start) << endl;
	system("pause");
	return 0;
}