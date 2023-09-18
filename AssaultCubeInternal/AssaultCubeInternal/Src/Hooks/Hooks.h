#pragma once

bool DetourHookX86(void* src, void* dst, int len);
BYTE* TrampolineHookX86(BYTE* src, BYTE* dst, const DWORD len);

class Hook
{
public:
	bool bStatus = false;

	BYTE* src = nullptr;
	BYTE* dst = nullptr;
	BYTE* ptrToGatewayPtr = nullptr;
	int len = 0;

	BYTE originalBytes[10]{ 0 };

	Hook(BYTE* src, BYTE* dst, BYTE* ptrToGatewayPtr, uintptr_t len);
	Hook(const char* exportName, const char* moduleName, BYTE* dst, BYTE* ptrToGatewayPtr, uintptr_t len);

	void Enable();
	void Disable();
	void Toggle();
};

namespace Hooks
{
	void Initialize();
	void Unhook();

	BOOL __stdcall hkwglSwapBuffers(HDC hDc);

	typedef BOOL(__stdcall* twglSwapBuffers)(HDC hDc);
	inline twglSwapBuffers wglSwapBuffersGateway;

	inline Hook swapBuffersHook("wglSwapBuffers", "opengl32.dll", (BYTE*)hkwglSwapBuffers, (BYTE*)&wglSwapBuffersGateway, 5);
}