#include <Windows.h>
#include <iostream>

void EchoSysInfo() {
	DWORD computer_name_length = MAX_COMPUTERNAME_LENGTH;
	WCHAR computer_name[MAX_COMPUTERNAME_LENGTH];
	if (GetComputerNameW(computer_name, &computer_name_length)) {
		// computer_name[computer_name_length - 1] = '\0';
		std::wcout << "计算机名:" << computer_name_length << computer_name << std::endl;
	}
	else {
		std::cout << "获取计算机名失败" << std::endl;
	}

	SYSTEM_INFO si = { 0 };
	GetSystemInfo(&si);
	std::wcout << "CPU 数量:" << si.dwNumberOfProcessors << std::endl;
	std::wcout << "CPU 类型：" << si.dwProcessorType << std::endl;
}

int main() {
	EchoSysInfo();

	std::cin.get();
	return 0;
}