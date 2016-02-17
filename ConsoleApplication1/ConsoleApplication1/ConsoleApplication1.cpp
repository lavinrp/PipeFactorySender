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

int main()
{
	//pipe
	LPTSTR pipeName = TEXT("\\\\.\\pipe\\testPipe");
	HANDLE hPipe;

	//size of data to pass
	DWORD outSize = 3 * sizeof(point3D);
	DWORD inSize = 3 * sizeof(point3D);
	DWORD bytesWritten;
	bool fSuccess = false;

	//create pipe
	hPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_MESSAGE, 1, outSize, inSize, NULL, NULL);

	//write point 3d
	bool end = false;
	int addition = 0;
	do 
	{
		point3D mesages[3];
		point3D mesage;
		mesage.x = 10 + addition;
		mesage.y = 20 + addition;
		mesage.z = 30 + addition;
		mesages[0] = mesage;
		mesages[1] = mesage;
		mesages[2] = mesage;

		fSuccess = WriteFile(hPipe, mesages, sizeof(mesages), &bytesWritten, NULL);
		cout << fSuccess << endl;

		addition += 100;
		cin >> end;
	} while (!end);

	//close pipe
	CloseHandle(hPipe);

    return 0;
}

