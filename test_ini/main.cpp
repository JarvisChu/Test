#include <iostream>
#include "Util.h"
#include "log.h"
#include <thread>

#define _CRT_SECURE_NO_WARNINGS

int main() {
    LOGGER;

    std::thread arr[10];

    for (int i = 0; i < 10; i++) {
        arr[i] = std::thread([i]() {
            LINFO("%s", "hello");
            LERROR("%d_%s", i, "world");
        });
    }

    for (int i = 0; i < 10; i++) {
        arr[i].join();
    }

    std::cout << Util::GetModuleFile() << std::endl;
    std::cout << Util::GetModuleName() << std::endl;
	std::cout << Util::GetModuleFileDir() << std::endl;
	std::cout << Util::GetCacheDir() << std::endl;
   
/*
	std::cout << Util::GetIniFileString("C:\\codde\\config\\utf8.ini", "environment", "name", "default") << std::endl;
	std::cout << Util::GetIniFileString("C:\\code\\config\\utf8bom.ini", "environment", "name", "default") << std::endl;
	std::cout << Util::GetIniFileString("C:\\code\\config\\ansi.ini", "environment", "name", "default") << std::endl;

	std::cout << Util::GetIniFileInt("C:\\code\\config\\utf8.ini", "environment", "number", -1) << std::endl;
	std::cout << Util::GetIniFileInt("C:\\code\\config\\utf8bom.ini", "environment", "number",-1) << std::endl;
	std::cout << Util::GetIniFileInt("C:\\code\\config\\ansi.ini", "environment", "number", -1) << std::endl;

	std::cout << Util::GetIniFileBool("C:\\code\\config\\utf8.ini", "environment", "log", false) << std::endl;
	std::cout << Util::GetIniFileBool("C:\\code\\config\\utf8bom.ini", "environment", "log", false) << std::endl;
	std::cout << Util::GetIniFileBool("C:\\code\\config\\ansi.ini", "environment", "log", false) << std::endl;


	std::cout << Util::SetIniFile("C:\\code\\config\\utf8.ini", "environment", "name", "default1") << std::endl;
	std::cout << Util::SetIniFile("C:\\code\\config\\utf8bom.ini", "environment", "name", "default1") << std::endl;
	std::cout << Util::SetIniFile("C:\\code\\config\\ansi.ini", "environment", "name", "default1") << std::endl;

	std::cout << Util::SetIniFile("C:\\code\\config\\utf8.ini", "environment", "name1", "default2") << std::endl;
	std::cout << Util::SetIniFile("C:\\code\\config\\utf8bom.ini", "environment", "name1", "default2") << std::endl;
	std::cout << Util::SetIniFile("C:\\code\\config\\ansi.ini", "environment", "name1", "default2") << std::endl;

	testGet("C:\\code\\config\\utf8.ini");
	testGet("C:\\code\\config\\utf8bom.ini");
	testGet("C:\\code\\config\\ansi.ini");

	testSet("C:\\code\\config\\utf8.ini");
	testSet("C:\\code\\config\\utf8bom.ini");
	testSet("C:\\code\\config\\ansi.ini");
	*/
	return 1;
}