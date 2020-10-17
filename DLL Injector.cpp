#include <Windows.h>
#include <iostream>
char DllName[MAX_PATH];
char PartialDllName[255];
char ProgramName[MAX_PATH];

DWORD pID;

bool bFileExists(LPCSTR szFileName)
{
	DWORD dwAttrib = GetFileAttributes(szFileName);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES);
}



int main()
{
	system("title Shitty Titty Injector by 84b");
	std::cout << "Enter the window name rn: ";
	std::cin.getline(ProgramName, sizeof(ProgramName));
	HWND Program = FindWindowA(NULL, ProgramName);
	if (Program == NULL) std::cerr << "Window not found.\n";

	else {
		GetWindowThreadProcessId(Program, &pID);
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
			if (hProcess == NULL) std::cerr << "Failed to open\n";

			else
			{
				std::cout << "\nEnter the DLL name: ";
				std::cin >> PartialDllName;
				if (!bFileExists((LPCSTR)PartialDllName))
				{
					std::cerr << "\nEnter a file that exists\n";
					return EXIT_FAILURE;
				}
				GetFullPathNameA(PartialDllName, MAX_PATH, DllName, NULL);
				LPVOID LoadLib = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
				LPVOID RemoteString = VirtualAllocEx(hProcess, NULL, strlen(DllName), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
				WriteProcessMemory(hProcess, RemoteString, DllName, strlen(DllName), NULL);
				CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLib, (LPVOID)RemoteString, NULL, NULL);
				std::cout << "Injected successfully.\nProgram will exit soon.\n";
				CloseHandle(hProcess);
				Sleep(7500);
				exit(0);
			}
	}
}
