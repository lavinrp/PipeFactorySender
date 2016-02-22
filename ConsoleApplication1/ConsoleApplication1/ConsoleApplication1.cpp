// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

struct point3D
{
	int x;
	int y;
	int z;
};

//server
int main()
{
	//pipe
	LPTSTR pipeName = TEXT("\\\\.\\pipe\\testPipe");
	HANDLE hPipe;

	//create pipe
	hPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);

	//handle bad pipe creation
	if (!hPipe || hPipe == INVALID_HANDLE_VALUE) 
	{
		cout << "failed to make pipe" << endl;
		cout << endl << endl << GetLastError() << endl;
		system("pause");
		return 1;
	}

	//Connect to consumer
	bool successfulConnection = ConnectNamedPipe(hPipe, NULL);

	//handle bad connection
	if (!successfulConnection) 
	{
		cout << "bad connection" << endl << endl;
		cout << GetLastError() << endl;
		system("pause");
		return 2;
	}

	//Data to write
	DWORD data[5] = { 1,2,3,4,5 };
	DWORD bytesWritten;

	//write data
	bool succcessfulWrite = WriteFile(
		hPipe,
		data,
		sizeof(data),
		&bytesWritten,
		NULL);

	//logic with written data
	if (succcessfulWrite)
	{
		cout << "sent " << bytesWritten << endl;
	}
	else
	{
		cout << "failed to send data" << endl;
	}

	//close pipe
	CloseHandle(hPipe);

	system("pause");
    return 0;
}

