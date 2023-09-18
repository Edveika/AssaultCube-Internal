#include "Includes.h"

// Main hack thread
DWORD WINAPI OnDllAttach(HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	srand(time(NULL));

	// Initialize the hooks
	Hooks::Initialize();

	while (!GetAsyncKeyState(VK_DELETE))
		Sleep(100);

	// Unhook hooks
	Hooks::Unhook();

	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

// DllMain
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// Create the main hack thread
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)OnDllAttach, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}