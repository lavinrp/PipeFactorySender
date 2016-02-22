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

	//connect to pipe
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

			//pipe found break connection loop
			if (hPipe != INVALID_HANDLE_VALUE) 
			{
				break;
			}

			//unexpected pipe error
			if (GetLastError() != ERROR_PIPE_BUSY) 
			{
				cout << "Unexpected Error: "<< GetLastError() << endl;
				return -1;
			}

			//only wait 20000 ms for pipe connection
			if (!WaitNamedPipe(pipeName, 20000)) 
			{
				cout << "cant open pipe" << endl;
				return -2;
			}
	}

	//If pipe is somehow still invalid throw error
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		cout << "Failed to connect to pipe" << endl;
	}

	//create buffer and bytesRead
	DWORD buffer[128];
	DWORD bytesRead = 0;

	//Read from pipe
	bool readResult = ReadFile(
		hPipe,					//pipe
		buffer,					//Write location
		127 * sizeof(DWORD),	//number of bytes to read
		&bytesRead,				//bytes read
		NULL);					//Overlapped

	//Run Logic on successful read
	if (readResult) 
	{
		cout << "read " << bytesRead << endl;
		for (unsigned int i = 0; i < bytesRead / sizeof(DWORD); i++) 
		{
			cout << (DWORD)buffer[i] << endl;
		}
	}
	//Output error on unsuccessful read
	else
	{
		cout << "error reading data" << endl;
		cout << endl << endl << GetLastError();
	}

	//clean up
	CloseHandle(hPipe);

	system("pause");
    return 0;
}

