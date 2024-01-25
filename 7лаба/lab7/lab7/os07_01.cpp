#include <iostream>
#include <Windows.h>
#include <ctime>
#include <iomanip>

using namespace std;

void main() {
    time_t t;
    t = time(&t);
    tm now;
    localtime_s(&now, &t);
    cout << now.tm_mday << '.' << now.tm_mon + 1 << '.' << now.tm_year + 1900 << ' ';
    cout << now.tm_hour << ':' << now.tm_min << ':' << now.tm_sec << endl;

    cout << put_time(&now, "%d.%m.%Y %H:%M:%S") << endl;

}