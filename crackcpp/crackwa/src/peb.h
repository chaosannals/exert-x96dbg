#ifndef PEB_H
#define PEB_H
#include <Windows.h>
#include "winter.h"

// ���
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
extern "C" BOOL HasHeapFlagByPEB();// ���ַ�ʽӦ�ÿ��У����������ҵ��Ĵ���Ӧ���Ǵ�ġ�
extern "C" VOID AxDivZero();
#else
extern "C" BOOL __stdcall HasPEBBeingDebuggedFlag();
extern "C" BOOL __stdcall HasPEBNtGlobalFlag();
extern "C" BOOL __stdcall HasHeapFlagByPEB();// ���ַ�ʽӦ�ÿ��У����������ҵ��Ĵ���Ӧ���Ǵ�ġ�
extern "C" VOID __stdcall AxDivZero();
#endif
#endif

// C �ں� API 

BOOL QueryInformationProcessByNt(BOOL *result) {
	int debugPort = 0;
	HMODULE hmodule = LoadLibraryW(L"ntdll.dll");
	NtQueryInformationProcessPtr NtQueryInformationProcess = (NtQueryInformationProcessPtr)GetProcAddress(hmodule, "NtQueryInformationProcess");
	if (NtQueryInformationProcess(GetCurrentProcess(), ProcessDebugPort, &debugPort, sizeof(debugPort), NULL)) {
		return FALSE;
	}
	*result = debugPort == -1;
	return TRUE;
}


VOID SetInformationThreadByNt() {
	HMODULE hmodule = LoadLibraryW(L"ntdll.dll");
	NtSetInformationThreadPtr NtSetInformationThread = (NtSetInformationThreadPtr)GetProcAddress(hmodule, "NtSetInformationThread");
	NtSetInformationThread(GetCurrentProcess(), ThreadHideFromDebugger, NULL, 0);
}


#endif
