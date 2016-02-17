// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

struct point3D
{
	int x;
	int y;
	int z;
};

//client
int main()
{

	//pipe
	LPTSTR pipeName = TEXT("\\\\.\\pipe\\testPipe");
	HANDLE hPipe;

	//size of data to pass
	//DWORD outSize = sizeof(int);
	//DWORD inSize = sizeof(int);
	//bool fSuccess = false;

	while (true)
	{
		hPipe = CreateFile(
			pipeName,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

			if (hPipe != INVALID_HANDLE_VALUE) {
				break;
			}

			if (GetLastError() != ERROR_PIPE_BUSY) {
				cout << "Unexpected Error: "<< GetLastError() << endl;
				return -1;
			}

			if (!WaitNamedPipe(pipeName, 20000)) {
				cout << "cant open pipe" << endl;
				return -2;
			}
	}

	if (hPipe == INVALID_HANDLE_VALUE)
	{
		cout << "Failed to connect to pipe" << endl;
	}

	wchar_t buffer[128];
	DWORD bytesRead = 0;

	bool readResult = ReadFile(
		hPipe,
		buffer,
		127 * sizeof(wchar_t),
		&bytesRead,
		NULL);


	if (readResult) {
		buffer[bytesRead / sizeof(wchar_t)] = '\0';
		cout << "read " << bytesRead << endl;
		cout << buffer << endl;
	}
	else
	{
		cout << "error reading data" << endl;
		cout << endl << endl << GetLastError();
	}

	CloseHandle(hPipe);

	system("pause");
    return 0;
}

