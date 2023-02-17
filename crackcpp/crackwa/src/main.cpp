#include <Windows.h>
#include "peb.h"

// 监听 EAX ,除0 异常时继续，如果被调试此函数不生效。
LONG WINAPI MyUnhandledExceptionFilter(_EXCEPTION_POINTERS* ep) {
#ifdef _WIN64
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ep->ContextRecord->Rax);
    ep->ContextRecord->Rip += 3;
#else
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ep->ContextRecord->Eax);
    ep->ContextRecord->Eip += 2;
#endif
    return EXCEPTION_CONTINUE_EXECUTION;
}

INT WINAPI wWinMain(
    _In_ HINSTANCE instance,
    _In_opt_ HINSTANCE prevInstance,
    _In_ LPWSTR    cmdLine,
    _In_ int       cmdShow) {

    SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);

    MessageBoxW(NULL, L"正常分支(start)", L"正常", MB_OK);

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

    if (HasHeapFlagByPEB()) {
        MessageBoxW(NULL, L"PEB 找到堆，查看堆标志判定", L"不能调试", MB_ICONERROR);
    }
    else {
        MessageBoxW(NULL, L"正常分支(step 5)", L"正常", MB_OK);
    }

    if (QueryInformationProcessByNt(&isDebug)) {
        if (isDebug) {
            MessageBoxW(NULL, L"NtQueryInformationProcess Debug 标志判定", L"不能调试", MB_ICONERROR);
        }
        else {
            MessageBoxW(NULL, L"正常分支(step 6)", L"正常", MB_OK);
        }
    }
    else {
        MessageBoxW(NULL, L"NtQueryInformationProcess 获取调试信息失败", L"错误", MB_ICONERROR);
    }

    // 关闭调试器，目前好像不可用（触发了异常，即使正常打开程序）。
    // SetInformationThreadByNt();

    AxDivZero();


    MessageBoxW(NULL, L"正常分支(end)", L"正常", MB_OK);
    return 0;
}