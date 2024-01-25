#include <iostream>
#include<Windows.h>

#include <process.h>
using namespace std;
int main()
{
    for (int i = 0; i < 1000; i++) {
        cout << i << " PID:" << _getpid() << endl;;
        Sleep(1000);
    }
}