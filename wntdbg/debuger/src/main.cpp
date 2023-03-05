#include <Windows.h>
#include <iostream>

WCHAR TargetCommand[] = L"buger.exe";
WCHAR WorkDir[MAX_PATH];

int main() {
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFOW si = { 0 };

	try {

		if (!CreateProcessW(
			NULL,
			TargetCommand,
			NULL,
			NULL,
			FALSE,
			//DEBUG_ONLY_THIS_PROCESS, // 只调试主进程
			DEBUG_PROCESS, // 调试
			NULL,
			NULL,
			&si,
			&pi
		)) {
			return -1;
		}

		std::cout << "debuger start" << std::endl;
		DEBUG_EVENT event;
		BOOL able = TRUE;
		INT yieldMs = 0;
		while (able) {
			if (WaitForDebugEvent(&event, 150)) {
				switch (event.dwDebugEventCode) {
				case CREATE_PROCESS_DEBUG_EVENT:
					std::cout << "CREATE_PROCESS_DEBUG_EVENT" << std::endl;
					break;
				case EXIT_PROCESS_DEBUG_EVENT:
					std::cout << "EXIT_PROCESS_DEBUG_EVENT" << std::endl;
					able = FALSE;
					break;
				case EXCEPTION_DEBUG_EVENT:
					std::cout << "EXCEPTION_DEBUG_EVENT" << std::endl;
					break;
				default:
					break;
				}
				ContinueDebugEvent(event.dwProcessId, event.dwThreadId, DBG_CONTINUE); // 不处理异常，直接执行。（第一次进入引发的异常或INT3必须采用就通过了。其他异常一般会不断发生）
				// ContinueDebugEvent(event.dwProcessId, event.dwThreadId, DBG_EXCEPTION_NOT_HANDLED); // 使用程序自带的异常处理程序。（如果有的话）
			}
			else {
				yieldMs += 150;
				if ((yieldMs % 15000) == 0) {
					std::cout << "yield:" << yieldMs << "ms" << std::endl;
				}
			}
		}
	}
	catch (...)
	{
		std::exception_ptr p = std::current_exception();
		std::cout << "exception" << std::endl;
	}

	return 0;
}