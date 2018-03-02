#include <dllmain.h>

// working around a bug in Hooking.Patterns x64 version
template<typename T = void>
auto get_pattern(const char *pattern_string, ptrdiff_t offset = 0)
{
	return hook::pattern(pattern_string).get_first<T>(offset);
}

void InitializeMod()
{
	OutputDebugStringA("// GTA V Heap Adjuster (build " __DATE__ ")\n");
	OutputDebugStringA("//     (C) CitizenFX Collective 2017\n");

	int* loc = hook::get_pattern<int32_t>("83 C8 01 48 8D 0D ? ? ? ? 41 B1 01 45 33 C0", 17);

	DWORD oldProtect;
	VirtualProtect(loc, 4, PAGE_EXECUTE_READWRITE, &oldProtect);

	*loc = 650 * 1024 * 1024; // 600 MiB, default in 323 was 412 MiB

	VirtualProtect(loc, 4, oldProtect, &oldProtect);
}

BOOL WINAPI DllMain(_In_ void* _DllHandle, _In_ unsigned long _Reason, _In_opt_ void* _Reserved)
{
	if (_Reason == DLL_PROCESS_ATTACH)
	{
		InitializeMod();
	}

	return TRUE;
}