// https://guidedhacking.com/
#include "../../Includes.h"

// Nop instructions
void Utils::Nop(BYTE* dst, unsigned int size)
{
	// Copy of current protection
	DWORD curProtection;

	// Get Read & Write permissions
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &curProtection);

	// Nop the bytes
	memset(dst, 0x90, size);

	// Restore Read & Write permissions
	VirtualProtect(dst, size, curProtection, &curProtection);
}

// Patch instructions
void Utils::Patch(BYTE* dst, BYTE* src, unsigned int size)
{
	// Current protection
	DWORD curProtection;

	// Get Read & Write permissions
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &curProtection);

	// Patch the bytes
	memcpy(dst, src, size);

	// Restore Read & Write permissions
	VirtualProtect(dst, size, curProtection, &curProtection);
}

// For multi-level pointers
DWORD Utils::FindDMAAddress(DWORD ptr, std::vector<unsigned int> offsets)
{
	// Copy of the ptr
	DWORD address = ptr;

	// Loop through the offsets
	for (unsigned int i = 0; i < offsets.size(); i++)
	{
		// Get the address by dereferencing & casting to DWORD ptr
		address = *(DWORD*)address;

		// Add offset values to our address
		address += offsets[i];
	}

	// Return the address w added offsets
	return address;
}

// Write to memory
void Utils::WriteToMemory(DWORD addressToWrite, const char* valueToWrite, int byteNum)
{
	// Current protection
	DWORD curProtection;

	// Get read & write permissions
	VirtualProtect((LPVOID)(addressToWrite), byteNum, PAGE_EXECUTE_READWRITE, &curProtection);

	// Write to memory
	memcpy((LPVOID)addressToWrite, valueToWrite, byteNum);

	// Restore read & write permissions
	VirtualProtect((LPVOID)(addressToWrite), byteNum, curProtection, NULL);
}

// Get module information
MODULEINFO GetModuleInfo(const char* szModule)
{
	// Module info
	MODULEINFO modInfo = { 0 };

	// Get module handle for szModule
	HMODULE hModule = GetModuleHandleA(szModule);

	// if hModule is equal to 0
	if (hModule == 0)
		// Just return null value
		return modInfo;

	// Get module information
	GetModuleInformation(GetCurrentProcess(), hModule, &modInfo, sizeof(MODULEINFO));

	// Return module information
	return modInfo;
}

// Pattern scanning
DWORD Utils::FindPattern(const char* module, const char* pattern, const char* mask)
{
	// Get module info
	MODULEINFO modInfo = GetModuleInfo(module);

	// Module base
	DWORD base = (DWORD)modInfo.lpBaseOfDll;

	// Module size
	DWORD size = (DWORD)modInfo.SizeOfImage;

	// Length of the pattern
	DWORD patternLength = (DWORD)strlen(mask);

	for (DWORD i = 0; i < size - patternLength; i++)
	{
		bool found = true;

		for (DWORD j = 0; j < patternLength; j++)
		{
			// If there is ? there, ignore it & move on
			// If pattern matched the character we are looking for
			found &= mask[j] == '?' || pattern[j] == *(const char*)(base + i + j);
		}

		// If by the end found is equals to true the pattern is found
		if (found)
			// Return base address + i
			return base + i;
	}

	// If nothing is found return null
	return NULL;
}