// print modules by Leopard Grelly.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <vector>

int getPidByName(const char* name) {
	int pid = 0;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_stricmp(entry.szExeFile, name) == 0)
			{
				pid = entry.th32ProcessID;
			}
		}
	}

	CloseHandle(snapshot);
	return pid;
}

void print_modules_of_the_process(DWORD dwProcessID)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessID);
	DWORD dwModuleBaseAddress = 0;
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry32 = { 0 };
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &ModuleEntry32))
		{
			do
			{
				printf("%s\n", ModuleEntry32.szModule);

			} while (Module32Next(hSnapshot, &ModuleEntry32));
		}
		CloseHandle(hSnapshot);
	}

}

int main()
{
	int pid = getPidByName("csgo.exe");
	if (pid)
		print_modules_of_the_process(pid);	
	else 
		printf("no such process\n");
	
	system("pause");
	return 0;
}

