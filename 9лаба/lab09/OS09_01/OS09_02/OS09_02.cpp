#include <Windows.h>
#include <iostream>

using namespace std;

#define FILE_PATH L"E:/уник/ОС/9лаба/lab09/OS09_01.txt"

BOOL printFileTxt(LPWSTR FileName);
BOOL DelRowFileTxt(LPWSTR FileName, DWORD row);


int main()
{
    setlocale(LC_CTYPE, "Rus");
    LPWSTR path = (LPWSTR)FILE_PATH;
    
    DelRowFileTxt(path, 1);
    DelRowFileTxt(path, 3);
    DelRowFileTxt(path, 8);
    DelRowFileTxt(path, 10);

    printFileTxt(path);
}


BOOL printFileTxt(LPWSTR path)
{
    HANDLE file = CreateFile(
        path,
        GENERIC_READ,
        NULL,
        NULL,
        OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    char buf[1024];
    DWORD countBytes = 0;

    ZeroMemory(buf, sizeof(buf));
    BOOL b = ReadFile(file, &buf, sizeof(buf) - 1, &countBytes, NULL);
    if (!b) throw "read file failed";

    cout << "\n-- Read file " << countBytes << " byte succesfull:\n" << buf << '\n';
}


BOOL DelRowFileTxt(LPWSTR FileName, DWORD row)
{
    BOOL b = FALSE;
    try
    {
        if ((int)row < 0)
            throw "Invalid row number";

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
        char* outbuf = new char[((PLARGE_INTEGER)(&fileSize))->QuadPart + 1];

        DWORD n = NULL;
        ZeroMemory(inbuf, ((PLARGE_INTEGER)(&fileSize))->QuadPart + 1);
        ZeroMemory(outbuf, ((PLARGE_INTEGER)(&fileSize))->QuadPart + 1);

        if (!ReadFile(file, inbuf, ((PLARGE_INTEGER)(&fileSize))->QuadPart, &n, NULL))
            throw "Read file error!";

        inbuf[((PLARGE_INTEGER)(&fileSize))->QuadPart] = NULL;
        
        int line = 1;

        for (int i = 0, j = 0; i < ((PLARGE_INTEGER)(&fileSize))->QuadPart + 1; i++)
        {
            if (line != (int)row)
                outbuf[j++] = inbuf[i];

            if (inbuf[i] == '\n')
                line++;
         
            if (inbuf[i] == '\0')
            {
                outbuf[j] = '\0';
                break;
            }
        }

        if ((int)row > line)
        {
            CloseHandle(file);
            return b;
        }

        SetFilePointer(file, 0, 0, FILE_BEGIN);

        if (!WriteFile(file, outbuf, strlen(outbuf), &n, NULL))
            throw "Write file error!";

        if (!SetEndOfFile(file))
            throw "End of file error!";
        CloseHandle(file);
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