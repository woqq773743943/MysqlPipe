//#include <iostream>

//using namespace std;

/*void main() {
	cout << "test" << endl;
	int data;
	while (cin >> data) {
		cout << data << endl;
	}
}*/

#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
int main()
{
	//setvbuf(stdout, NULL, _IONBF, NULL);
	//fprintf(stderr, "c\n");
	//cout << "c";
	DWORD size;
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),"test",4,&size,NULL);
	//printf("c\n");
	getchar();
}