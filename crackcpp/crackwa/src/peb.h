#ifndef PEB_H
#define PEB_H
#include <Windows.h>

#ifdef __clang__
#ifdef _WIN64
BOOL __stdcall HasPEBBeingDebuggedFlag() {
	char result = 0;
	__asm {
		mov rax, QWORD PTR gs:[60h]
		mov al, BYTE PTR[rax + 2]
		mov result, al
	}
	return result != 0;
}
#else
BOOL __stdcall HasPEBBeingDebuggedFlag() {
	char result = 0;
	__asm {
		mov eax, fs:[30h]
		mov al, BYTE PTR[eax + 2]
		mov result, al
	}
	return result != 0;
}
#endif
#else
#ifdef _WIN64
extern "C" BOOL HasPEBBeingDebuggedFlag();
extern "C" BOOL HasPEBNtGlobalFlag();
#else
extern "C" BOOL __stdcall HasPEBBeingDebuggedFlag();
extern "C" BOOL __stdcall HasPEBNtGlobalFlag();
#endif
#endif

#endif
