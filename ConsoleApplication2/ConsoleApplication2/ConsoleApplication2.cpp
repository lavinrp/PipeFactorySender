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

int main()
{

	//pipe
	LPTSTR pipeName = TEXT("\\\\.\\pipe\\testPipe");
	HANDLE hPipe;

	//size of data to pass
	DWORD outSize = sizeof(int);
	DWORD inSize = sizeof(int);
	DWORD bytesRead;
	bool fSuccess = false;

	while (true)
	{
		hPipe = CreateFile(
			pipeName,
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_ALWAYS,
			NULL,
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

	do {
		//read from pipe
		point3D points[3];

		fSuccess = ReadFile(
			hPipe,
			points,
			sizeof(points),
			&bytesRead,
			nullptr);

		if (!fSuccess && GetLastError() != ERROR_MORE_DATA) {
			cout << "Unexpected Error: " << GetLastError() << endl;
			return -3;
		}

		for (unsigned int i = 0; i < 3; i++) {
			point3D pointI = points[i];
			cout << "point" << i << ":\r\nx: " << pointI.x << "\r\ny: " << pointI.y << "\r\nz: " << pointI.z << endl;
		}

	} while (!fSuccess);


    return 0;
}

