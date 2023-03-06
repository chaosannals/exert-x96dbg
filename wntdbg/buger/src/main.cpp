#include <iostream>
#include <Windows.h>

void EchoSysInfo() {
	DWORD computer_name_length = MAX_COMPUTERNAME_LENGTH;
	WCHAR computer_name[MAX_COMPUTERNAME_LENGTH];
	if (GetComputerNameW(computer_name, &computer_name_length)) {
		std::wcout << "�������:" << computer_name_length << computer_name << std::endl;
	}
	else {
		std::cout << "��ȡ�������ʧ��" << std::endl;
	}

	SYSTEM_INFO si = { 0 };
	GetSystemInfo(&si);
	std::wcout << "CPU ����:" << si.dwNumberOfProcessors << std::endl;
	std::wcout << "CPU ���ͣ�" << si.dwProcessorType << std::endl;
}

int main() {
	std::cout << "start" << std::endl;
	EchoSysInfo();
	std::cin.get();
	std::cout << "end" << std::endl;
	return 0;
}