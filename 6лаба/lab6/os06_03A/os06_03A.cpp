#include <iostream>
#include <Windows.h>
using namespace std;

int main()
{
	HANDLE hm = OpenMutex(SYNCHRONIZE, FALSE, L"Mutex");
	if (hm == NULL)
	{
		cout << "3A: Open Mutex error\n";
	}
	else
	{
		cout << "3A: Open Mutex\n";
	}

	for (int i = 0; i < 90; i++)
	{
		if (i == 30)
		{
			WaitForSingleObject(hm, INFINITE);
		}

		cout << "3A: " << i << " PID: " << GetCurrentProcessId() << endl;

		if (i == 60)
		{
			ReleaseMutex(hm);
		}
		Sleep(100);

	}

	system("pause");

}
