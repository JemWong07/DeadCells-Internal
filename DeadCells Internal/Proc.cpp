#include "Proc.h"

DWORD GetProcID(const wchar_t* procName)
{
	DWORD procID{ 0 };
	//	Create a handle that contains all processes in the snapshot.
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procEntry;
		//	We need to initialize the size first before calling Process32First.
		procEntry.dwSize = sizeof(procEntry);
		// Copy the first process into the buffer.
		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				//	Compare the buffer's process name with desired process name.
				//	If matched.
				if (_wcsicmp(procEntry.szExeFile, procName) == 0)
				{
					//	Copy the desired buffer's process id into procID variable.
					procID = procEntry.th32ProcessID;
					break;
				}
			}
			//	if the next process is copied to the buffer, check the copied process.
			while (Process32Next(hSnap, &procEntry));
		}
	}
	//	Close the handle and return the process id.
	CloseHandle(hSnap);
	return procID;
}

//	Basically same as GetProcID
uintptr_t GetModuleBaseAddress(DWORD procID, const wchar_t* modName)
{
	uintptr_t modBaseAddress{ 0 };
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (_wcsicmp(modEntry.szModule, modName) == 0)
				{
					//	The datatype of modEntry.modBaseAddr is BYTE, cast it to uintptr_t.
					modBaseAddress = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddress;
}
