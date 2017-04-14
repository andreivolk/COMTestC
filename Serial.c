#include <Serial.h>
#include <windows.h>
#include <string.h>
#include <stdio.h>


	HANDLE hSerial;
	DCB hSerialSettings = {0};

int GetPorts()
{
	char *PORTS[10] = {0};
	char usePort[100] = "";
	int k = 0;
	int com_check_flag  = 3;
	printf("Detecting ports...\n");
	while(k < 10) 
	{
		strcpy(usePort, PortName(k));
		hSerial = CreateFile(usePort, GENERIC_READ | GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
		if(hSerial==INVALID_HANDLE_VALUE)
		{
			com_check_flag = 1;
		}
		else
		{
			com_check_flag = 0;
			PORTS[k] = (char *) malloc(10);
			strncpy(PORTS[k], usePort, 10);
			CloseHandle(hSerial);
			Sleep(800);
		}
		if(k >= 9)
		{
			printf("Found ports:\n");
			for(int i = 0;i<10;i++)
			{
				if(PORTS[i]!=0)
				printf("%s \n",PORTS[i]);
			}
		}
		k++;
	}
	return 0;
}

char * PortName(int number)
{
		char str[10];
		char port[3] = "COM";
		char port1[10] = "\\\\\.\\";
		sprintf(str, "%d", number);
		strcat(port,str); 
		char *newPort = strcat(port1,port);
		return newPort;
}

int OpenPort(int port)
{
	hSerial = CreateFile(PortName(port), GENERIC_READ | GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
		if(hSerial==INVALID_HANDLE_VALUE)
		{
			printf("Failed to open port\n");			
		}
		else
		{
			hSerialSettings.DCBlength = sizeof(hSerialSettings);
			if (GetCommState(hSerial, &hSerialSettings) == 0)
			{
			printf("Error getting COM state.\n");
			CloseHandle(hSerial);
			return 1;
			}
			else
			{
			hSerialSettings.BaudRate = CBR_9600;
			hSerialSettings.ByteSize = 8;
			hSerialSettings.StopBits = ONESTOPBIT;
			hSerialSettings.Parity = NOPARITY;
			if(SetCommState(hSerial, &hSerialSettings) == 0)
			{
			printf("Error setting COM parameters.\n");
			CloseHandle(hSerial);
			return 1;
			}
			}
			printf("Port Open\n");
		}
		return 0;
}

int ClosePort()
{
	if (hSerial < 0) 
		{
			CloseHandle(hSerial);
			printf("Port Closed\n");
			return 1;
		}
	else
	{
		printf("No port open\n");
		return -1;
	}
}

int Send(char *message)
{
		if (hSerial < 0) 
		{
		printf("No COM port open.\n");
		return -1;
		}
		else
		{
			DWORD bytes_written, total_bytes_written = 0;
			printf("Sending message.\n");
			if(!WriteFile(hSerial, message, strlen(message), &bytes_written, NULL))
			{
			fprintf(stderr, "Error\n");
			CloseHandle(hSerial);
			return 1;
			}   
			printf("Message sent.\n");
		}
		return 0;
}

int Repeat(char *message)
{
	int i;
		for(i = 0;i<10;i++)
		{
			Send(message);
			Sleep(5000);
		}
		return 0;
}