#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

void invoke(string exe);

int main(int argc, char* argv[])
{
	string exe = "C:\\Users\\DALAOCHEN\\Desktop\\mysql-5.7.10\\bld\\client\\Debug\\mysql.exe -uroot -proot";
	//string exe = "hello.exe";
	invoke(exe);
	return 0;
}


void invoke(string exe)
{
	SECURITY_ATTRIBUTES saPipe;
	saPipe.nLength = sizeof(SECURITY_ATTRIBUTES);
	saPipe.lpSecurityDescriptor = NULL;
	saPipe.bInheritHandle = TRUE;

	HANDLE hInReadPipe, hInWritePipe;
	if (!CreatePipe(&hInReadPipe,
		&hInWritePipe,
		&saPipe,
		0))
		return;

	HANDLE hOutReadPipe, hOutWritePipe;
	if (!CreatePipe(&hOutReadPipe,
		&hOutWritePipe,
		&saPipe,
		0))
		return;
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.hStdInput = hInReadPipe;
	si.hStdError = hOutWritePipe;
	si.hStdOutput = hOutWritePipe;
	si.dwFlags = STARTF_USESTDHANDLES;
	si.cb = sizeof(si);

	if (CreateProcess(NULL, (char *)exe.c_str(), NULL, NULL, 1, 0, NULL, NULL, &si, &pi))
	{
		CloseHandle(pi.hThread);
		const int max = 20*1024;
		char buf[max] = { 0 };
		DWORD dw;
		//ReadFile(hOutReadPipe, buf, max - 1, &dw, NULL);
		//cout << buf << endl;
		WriteFile(hInWritePipe, "show databases;\n", strlen("show databases;\n"), &dw, NULL);
		//WriteFile(hInWritePipe, "quit\n", strlen("quit\n"), &dw, NULL);
		while(ReadFile(hOutReadPipe, buf, max - 1, &dw, NULL))
			cout << buf << endl;
		CloseHandle(pi.hProcess);
	}

	CloseHandle(hInReadPipe);
	CloseHandle(hInWritePipe);
	CloseHandle(hOutWritePipe);
	CloseHandle(hOutReadPipe);
}
