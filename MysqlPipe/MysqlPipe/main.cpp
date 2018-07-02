#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;

void invoke(string exe);

int main(int argc, char* argv[])
{
	string exe = "C:\\Users\\DALAOCHEN\\Desktop\\mysql-5.7.10\\bld\\client\\Debug\\mysql.exe -uroot -proot";
	invoke(exe);
	return 0;
}


void invoke(string exe)
{
	SECURITY_ATTRIBUTES saPipe;
	saPipe.nLength = sizeof(SECURITY_ATTRIBUTES);
	saPipe.lpSecurityDescriptor = NULL;
	saPipe.bInheritHandle = TRUE;

	HANDLE hReadPipe, hWritePipe;
	BOOL bSuccess = CreatePipe(&hReadPipe,
		&hWritePipe,
		&saPipe,
		0);
	if (!bSuccess)
		return;

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.hStdInput = hReadPipe;
	si.hStdOutput = hWritePipe;
	si.dwFlags = STARTF_USESTDHANDLES;
	si.cb = sizeof(si);

	if (CreateProcess(NULL, (char*)exe.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
	{
		CloseHandle(pi.hThread);
		const int max = 500;
		char buf[max] = { 0 };
		DWORD dw;

		if (ReadFile(hReadPipe, buf, max - 1, &dw, NULL))
		{
			cout << buf << endl;
			//			ZeroMemory(buf,max);
		}

		CloseHandle(pi.hProcess);
	}

	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
}
