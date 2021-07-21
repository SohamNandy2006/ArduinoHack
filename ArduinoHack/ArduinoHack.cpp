#include "stdafx.h"
#include "HackProcess.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "SerialPort.h"
#include <cstring>
#include <cstdio>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Advapi32.lib")

using namespace std;

CHackProcess fProcess;
DWORD LocalPlayerBase = 0xC5F89C;
DWORD PlayerBase;
DWORD CrosshairId = 0xB2B8;
int id;

//String for getting the output from arduino
char output[MAX_DATA_LENGTH];

/*Portname must contain these backslashes, and remember to
replace the following com port*/
char* port_name = "\\\\.\\COM5";

//String for incoming data
char incomingData[MAX_DATA_LENGTH];
string GG = "A";

//ruNSetDebugPrivs


int main()
{
	SerialPort arduino(port_name);
	if (arduino.isConnected()) cout << "Connection Established to Serial...\n";
	else cout << "Error, check your COM serial.\n";

	fProcess.RunProcess();


	while (arduino.isConnected()) {

		// wrap in condition

		//Read some stuff
		ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + LocalPlayerBase), &PlayerBase, sizeof(DWORD), 0);
		ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(PlayerBase + CrosshairId), &id, sizeof(DWORD), 0);

		if (GetAsyncKeyState(VK_XBUTTON2) && id > 0)
		{
			//Creating a c string
			char* c_string = new char[GG.size() + 1];
			//copying the std::string to c string
			std::copy(GG.begin(), GG.end(), c_string);
			//Adding the delimiter
			c_string[GG.size()] = '\n';
			//Writing string to arduino
			arduino.writeSerialPort(c_string, MAX_DATA_LENGTH);
			//freeing c_string memory
			delete[] c_string;

			// wrap in condition
		}
		Sleep(1);
	}
}
