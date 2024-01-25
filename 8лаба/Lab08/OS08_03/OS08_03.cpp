#include <iostream>
#include <Windows.h>

using namespace std;

#define PAGE_SIZE (4096)
int numPages = 256;

int main() {
    setlocale(LC_ALL, "rus");

    int* arr = (int*)VirtualAlloc(NULL, numPages * PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE);

    for (int i = 0; i < numPages * PAGE_SIZE / sizeof(int); i++) {
        arr[i] = i;
    }

    /*
        Г=195=C3
	    у=243=F3
	    р=240=F0
	    Страница C3 = 195, смещение F3F = 3903         --E5F=3679

	    адрес страницы 4096 * 195 = 798 720(10) = 0x000C3000
	    смещение 0x00000F3F => 3903     ??? (3676)
        адрес смещения = 798 720 + 3903 = 802 623, 0xC3F3F
	    (802 623)/4 (sizeof(int) = 4) = ???? 210839 = 33797
    */

    const int targetPage = 195;
    const int offset = 3903;

    int* value = arr + (targetPage * PAGE_SIZE + offset) / sizeof(int);

    cout << "Значение: " << *value << endl;
    cout << "Адрес: " << hex << value << endl;

    system("pause");

    return 0;
}