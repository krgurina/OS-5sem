#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	HANDLE hs = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Sem");
	if (hs == NULL)
	{
		cout << "4B: Open error Semaphore\n";
	}
	else
	{
		cout << "4B: Open Semaphore\n";
	}

	LONG prevcount = 0;
	for (int i = 0; i < 90; i++)
	{
		if (i == 30)
		{
			WaitForSingleObject(hs, INFINITE);
		}
		if (i == 60)
		{
			ReleaseSemaphore(hs, 1, &prevcount);
			cout << "4B: prevcount = " << prevcount << endl;
		}
		Sleep(100);
		cout << "4B: " << i << " PID: " << GetCurrentProcessId() << endl;
	}
	CloseHandle(hs);
	system("pause");

	return 0;
}
