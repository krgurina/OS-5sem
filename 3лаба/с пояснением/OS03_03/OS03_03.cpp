#include <iostream>
#include<Windows.h>
#include<TlHelp32.h>
#include<iomanip>
#include <process.h>
#include<string>
using namespace std;
int main()
{
    //извлечение ID  вызывающего процесса
    //
    DWORD pid = GetCurrentProcessId();                       
    //cоздает снапшот(фотография состояния) запущенных 
    //процессов, модулей, нитей и так далее
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPALL,//нужно собрать информацию о всех процессах,
        0); //снимок будет создан для текущей сессии.
    //Описывает запись из списка процессов, 
    //находящихся в системном адресном пространстве при создании моментального снимка.
    PROCESSENTRY32 peProcessEntry;  //струкутра для хранения информации о процессах.

    peProcessEntry.dwSize = sizeof(PROCESSENTRY32); //размер структуры в байтах
    cout << L"Current PID = " << pid << endl << L"-------------------" << endl;
    try {
        //Process32First инициализирует структуру peProcessEntry информацией о первом процессе. 
        if (!Process32First(snap, &peProcessEntry))
            throw L"Process32First";

        //перебираются все процессы с помощью функции Process32Next
        do {
            wcout << L"Name = " << peProcessEntry.szExeFile << endl
                << L"PID = " << peProcessEntry.th32ProcessID
                << L", Parent PID = " << peProcessEntry.th32ParentProcessID;

            if (peProcessEntry.th32ProcessID == pid)
                wcout << " --> current process";

            wcout << endl << L"----------------------" << endl;

        } while (Process32Next(snap, &peProcessEntry));
    }
    catch (wchar_t* msg) {
        wcout << L"Error : " << msg << endl;
    }
    system("pause");
    return 0;
}