#include <iostream>
#include <Windows.h>
#include <ctime>

using namespace std;

int mutex = 0;

DWORD WINAPI Thread();
int main() {

	HANDLE hChild = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, NULL, 0, NULL);
	HANDLE hChild2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, NULL, 0, NULL);
	ResumeThread(hChild);
	ResumeThread(hChild2);
	WaitForSingleObject(hChild, INFINITE);
	WaitForSingleObject(hChild2, INFINITE);
	CloseHandle(hChild);
	CloseHandle(hChild2);
	system("pause");
}

void enter_critical_section(void)
{
	__asm {
	Lloop:
		lock bts mutex, 0;
		jc Lloop
	}
}

void exit_critical_section(void)
{
	__asm lock btr mutex, 0
}

DWORD WINAPI Thread()
{
	DWORD tid = GetCurrentThreadId();

	enter_critical_section();
	for (int i = 0; i < 50; i++)
	{
		cout << "Thread: " << tid << "  " << i << endl;
	}
	exit_critical_section();

	return 0;
}