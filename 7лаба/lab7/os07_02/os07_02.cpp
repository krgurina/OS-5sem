#include <iostream>
#include <ctime>

using namespace std;

int main()
{
	clock_t t1 = clock();
	int i = 0;
	bool flag5 = true;
	bool flag10 = true;

	while (true) {
		i++;
		if (flag5 && (clock() - t1) / CLOCKS_PER_SEC == 5) {
		//if ((clock() - t1) / CLOCKS_PER_SEC == 5 && flag5) {
			cout << "5 : " << i << endl;
			flag5 = false;
		}
		if (flag10 && (clock() - t1) / CLOCKS_PER_SEC == 10) {
		//if ((clock() - t1) / CLOCKS_PER_SEC == 10 && flag10) {
			cout << "10 : " << i << endl;
			flag10 = false;
		}
		if ((clock() - t1) / CLOCKS_PER_SEC == 15) {
			cout << "15: " << i << endl;
			break;
		}
	}
	system("pause");
}