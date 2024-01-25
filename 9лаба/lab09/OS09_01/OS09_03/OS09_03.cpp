#define _CRT_NON_CONFORMING_WCSTOK
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include "Windows.h"

using namespace std;

#define FILE_PATH L"E:/уник/ОС/9лаба/lab09/OS09_01.txt"
BOOL InsRowFileTxt(LPWSTR FileName, LPWSTR str, DWORD row);
BOOL printFileTxt(LPWSTR FileName);

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    LPWSTR fileName = (LPWSTR)FILE_PATH;

    printFileTxt(fileName);

    InsRowFileTxt(fileName, (wchar_t*)L"New line0", 0);
    InsRowFileTxt(fileName, (wchar_t*)L"New line-1", -1);
    InsRowFileTxt(fileName, (wchar_t*)L"New line5", 5);
    InsRowFileTxt(fileName, (wchar_t*)L"New line7", 7);
    Sleep(50);

    printFileTxt(fileName);

}

BOOL printFileTxt(LPWSTR FileName)
{
    LPBY_HANDLE_FILE_INFORMATION lpFileInformation = new BY_HANDLE_FILE_INFORMATION();
    DWORD fileType;
    PLARGE_INTEGER fileSize = new LARGE_INTEGER();
    try
    {
        HANDLE of = CreateFile(
            FileName,
            GENERIC_READ,
            NULL,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
        if (of == INVALID_HANDLE_VALUE)
        {
            CloseHandle(of);
            throw "Open file failed";
        }

        if (GetFileSizeEx(of, fileSize))
        {
            char* buf = new char[fileSize->QuadPart * sizeof(char)];
            ZeroMemory(buf, sizeof(buf));
            DWORD n = NULL;
            if (ReadFile(of, buf, fileSize->QuadPart, &n, NULL))
            {
                buf[fileSize->QuadPart] = '\0';
               
                printf("\n-- Read file:%d byte successful:\n%s\n", n, buf);
            }
            else
            {
                CloseHandle(of);
                throw "ReadFile failed";
            }
        }
        else
        {
            CloseHandle(of);
            throw "GetFileSizeEx failed";
        }
        CloseHandle(of);
    }
    catch (const char* err)
    {
        std::cout << "--- Error:\n" << err << "\n";
        return false;
    }
    return true;
}

BOOL InsRowFileTxt(LPWSTR FileName, LPWSTR str, DWORD row)
{
    BOOL b = FALSE;
    try
    {
        WIN32_FIND_DATA data;
        HANDLE file = CreateFile(FileName,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL);

        if (file == INVALID_HANDLE_VALUE)
            throw "Open file error!";

        LARGE_INTEGER fileSize;
        if (!GetFileSizeEx(file, &fileSize))
            throw "File size error!";

        char* inbuf = new char[((PLARGE_INTEGER)(&fileSize))->QuadPart + 1];
        char* outbuf = new char[(((PLARGE_INTEGER)(&fileSize))->QuadPart) * 2];
        
        DWORD n = NULL;

        ZeroMemory(inbuf, ((PLARGE_INTEGER)(&fileSize))->QuadPart + 1);
        ZeroMemory(outbuf, ((PLARGE_INTEGER)(&fileSize))->QuadPart * 2);
        
        if (!ReadFile(file, inbuf, ((PLARGE_INTEGER)(&fileSize))->QuadPart, &n, NULL))
            throw "Read file error!";
        
        inbuf[((PLARGE_INTEGER)(&fileSize))->QuadPart] = NULL;
        
        int line = 1;
        int flag = 0;

        for (int i = 0, j = 0; i < ((PLARGE_INTEGER)(&fileSize))->QuadPart + 1; i++)
        {
            if (inbuf[i] != '\0')
            {
                outbuf[j++] = inbuf[i];
            }

            //Обработка первой строки для вставки
            if (inbuf[i] != '\0' && (row == (DWORD)1 || row == (DWORD)0) && i == 0)
            {
                j--;
                char* cstr = new char(wcslen(str));
                size_t length;
                wcstombs_s(&length, cstr, wcslen(str) * sizeof(wchar_t), str, wcslen(str) * sizeof(wchar_t));
                
                strcpy_s(&outbuf[j], length, cstr);

                j += strlen(cstr);
                
                outbuf[j++] = '\r';
                outbuf[j++] = '\n';

                line++;
                flag = 1;

                outbuf[j++] = inbuf[i];
                row = NULL;
            }

            if (inbuf[i] == '\n')
                line++;

            if (line == row)
            {
                char* cstr = new char(wcslen(str));
                size_t length;
                wcstombs_s(&length, cstr, wcslen(str) * sizeof(wchar_t), str, wcslen(str) * sizeof(wchar_t));
                
                strcpy_s(&outbuf[j], length, cstr);
                
                j += strlen(cstr);
                outbuf[j++] = '\r';
                outbuf[j++] = '\n';
                line++;
                flag = 1;
            }

            //вставить последнюю строку в файл
            if ((i == ((PLARGE_INTEGER)(&fileSize))->QuadPart && (line + 1 == (int)row || row == (DWORD)-1)))
            {
                char* cstr = new char(wcslen(str));
                size_t length;
                wcstombs_s(&length, cstr, wcslen(str) * sizeof(wchar_t), str, wcslen(str) * sizeof(wchar_t));
                
                outbuf[j++] = '\r';
                outbuf[j++] = '\n';
                
                strcpy_s(&outbuf[j], length, cstr);
                j += strlen(cstr);
                
                outbuf[j++] = '\0';
                line++;
                flag = 1;
            }


            if (inbuf[i] == NULL)
            {
                outbuf[j] = NULL;
                break;
            }
        }

        SetFilePointer(file, 0, 0, FILE_BEGIN);

        if (!WriteFile(file, outbuf, strlen(outbuf), &n, NULL))
            throw "Write file error!";

        if (!SetEndOfFile(file))
            throw "End of file error!";

        CloseHandle(file);

        if (!flag)
            throw "Invalid row number";
        b = true;
        delete[] inbuf;
        delete[] outbuf;
    }
    catch (const char* exception)
    {
        cerr << exception << endl;
    }
    return b;
}
