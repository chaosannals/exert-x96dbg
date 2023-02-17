#include <Windows.h>
#include "peb.h"

INT WINAPI wWinMain(
    _In_ HINSTANCE instance,
    _In_opt_ HINSTANCE prevInstance,
    _In_ LPWSTR    cmdLine,
    _In_ int       cmdShow) {

    BOOL isDebug = IsDebuggerPresent();

    if (isDebug) {
        MessageBoxW(NULL, L"IsDebuggerPresent 判定", L"不能调试", MB_ICONERROR);
    }
    else {
        MessageBoxW(NULL, L"正常分支(step 1)", L"正常", MB_OK);
    }

    // if (CheckRemoteDebuggerPresent(instance, &isDebug)) {
    if (CheckRemoteDebuggerPresent(GetCurrentProcess(), &isDebug)) {
        if (isDebug) {
            MessageBoxW(NULL, L"CheckRemoteDebuggerPresent 判定", L"不能调试", MB_ICONERROR);
        }
        else {
            MessageBoxW(NULL, L"正常分支(step 2)", L"正常", MB_OK);
        }
    }
    else {
        DWORD err = GetLastError();
        WCHAR msg[1024];
        FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), msg, 255, NULL);
        MessageBoxW(NULL, msg, L"CheckRemoteDebuggerPresent 判定失败", MB_ICONERROR);
    }

    if (HasPEBBeingDebuggedFlag()) {
        MessageBoxW(NULL, L"PEB BeingDebugged 判定", L"不能调试", MB_ICONERROR);
    }
    else {
        MessageBoxW(NULL, L"正常分支(step 3)", L"正常", MB_OK);
    }

    // 这个 VS 调试的时候不会设置。WinDbg 会设置。
    if (HasPEBNtGlobalFlag()) {
        MessageBoxW(NULL, L"PEB NtGlobal 判定", L"不能调试", MB_ICONERROR);
    }
    else {
        MessageBoxW(NULL, L"正常分支(step 4)", L"正常", MB_OK);
    }

    return 0;
}