#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	HANDLE he = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Event");

	if (he == NULL)
	{
		cout << "5B: Open Event error\n";
	}
	else
	{
		cout << "5B: Open Event\n";
	}

	WaitForSingleObject(he, INFINITE);
	for (int i = 1; i <= 90; i++)
	{
		//SetEvent(he);
		Sleep(100);
		cout << "5B: " << i << " PID: " << GetCurrentProcessId() << endl;
	}
	CloseHandle(he);
	system("pause");

	return 0;
}
