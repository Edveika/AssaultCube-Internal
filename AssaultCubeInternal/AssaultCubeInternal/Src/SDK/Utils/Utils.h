#pragma once

namespace Utils
{
	void Nop(BYTE* dst, unsigned int size);
	void Patch(BYTE* dst, BYTE* src, unsigned int size);
	void WriteToMemory(DWORD addressToWrite, const char* valueToWrite, int byteNum);
	DWORD FindDMAAddress(DWORD ptr, std::vector<unsigned int> offsets);
	DWORD FindPattern(const char* module, const char* pattern, const char* mask);
}