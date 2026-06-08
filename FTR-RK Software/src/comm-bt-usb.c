// This File will be used for functions realted to USB Communcation / BT Communication as well as initialization of these components

#pragma once
#include "globals.h"
#include <windows.h>
#include <stdbool.h>

#define dcbSerialParamsByteSize 8;

int comm_init(struct GlobalContext* ctx) {

	char portName[20];

	// Condition checks to ensure all data is present for completion of the function

	if (ctx->config.comPortNumber == 0) {
		
		// LOG ERROR to Log file either here or in main.c (need to decide how this want to be done)

		return -3;
	}

	if (ctx->config.baudRate == 0) {

		// LOG ERROR to Log file either here or in main.c (need to decide how this want to be done)

		return -2;
	}

	// Get COM port Information and format it for Windows API
	snprintf(portName, sizeof(portName), "\\\\.\\COM%d", ctx->config.comPortNumber);

	// Open the serial port and configure the serial parameters can do GENERIC_READ | GENERIC_WRITE but need to make sure serial.availiable happends on ESP because this can cause windows program to fail if it doesnt write properly
	ctx->hComPort = CreateFileA(portName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);


	if (ctx->hComPort == INVALID_HANDLE_VALUE) {

		DWORD error = GetLastError();

		// LOG ERROR to Log file either here or in main.c (need to decide how this want to be done)

		return -1;
	}

	// Configure Serial Parameters
	DCB dcbSerialParams = { 0 };

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	if (!GetCommState(ctx->hComPort, &dcbSerialParams)) {
		//Log error for failing to get serial state
		return -4;
	}

	dcbSerialParams.BaudRate = ctx->config.baudRate;
	dcbSerialParams.ByteSize = dcbSerialParamsByteSize;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	SetCommState(ctx->hComPort, &dcbSerialParams);

	// Set Timeouts
	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	SetCommTimeouts(ctx->hComPort, &timeouts);

	return 0;
}

DWORD WINAPI comm_listener_thread(LPVOID lpParam) {

}

void com_close(struct GlobalContext* ctx) {

}

bool com_is_connected(struct GlobalContext* ctx) {
	return true;
}