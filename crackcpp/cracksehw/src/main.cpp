#include <Windows.h>

INT WINAPI wWinMain(
    _In_ HINSTANCE instance,
    _In_opt_ HINSTANCE prevInstance,
    _In_ LPWSTR    cmdLine,
    _In_ int       cmdShow
) {
    int i = 0;
loop:
    __try {
        if (i++ < 1000) {
            // 非法内存访问触发异常
            volatile int* p = (int*)0x0000000;
            *p = 20;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        if (i == 1000) {
            MessageBoxW(NULL, L"SEH 异常结束", L"异常防调试", MB_ICONERROR);
        }
        goto loop;
    }

    return 0;
}