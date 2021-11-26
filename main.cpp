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

    std::cout << DolphinUtil::GetModuleFile() << std::endl;
    std::cout << DolphinUtil::GetModuleName() << std::endl;
	std::cout << DolphinUtil::GetModuleFileDir() << std::endl;
	std::cout << DolphinUtil::GetCacheDir() << std::endl;
   
/*
	std::cout << DolphinUtil::GetIniFileString("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\utf8.ini", "environment", "name", "default") << std::endl;
	std::cout << DolphinUtil::GetIniFileString("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\utf8bom.ini", "environment", "name", "default") << std::endl;
	std::cout << DolphinUtil::GetIniFileString("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\ansi.ini", "environment", "name", "default") << std::endl;

	std::cout << DolphinUtil::GetIniFileInt("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\utf8.ini", "environment", "number", -1) << std::endl;
	std::cout << DolphinUtil::GetIniFileInt("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\utf8bom.ini", "environment", "number",-1) << std::endl;
	std::cout << DolphinUtil::GetIniFileInt("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\ansi.ini", "environment", "number", -1) << std::endl;

	std::cout << DolphinUtil::GetIniFileBool("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\utf8.ini", "environment", "log", false) << std::endl;
	std::cout << DolphinUtil::GetIniFileBool("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\utf8bom.ini", "environment", "log", false) << std::endl;
	std::cout << DolphinUtil::GetIniFileBool("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\ansi.ini", "environment", "log", false) << std::endl;


	std::cout << DolphinUtil::SetIniFile("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\utf8.ini", "environment", "name", "default1") << std::endl;
	std::cout << DolphinUtil::SetIniFile("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\utf8bom.ini", "environment", "name", "default1") << std::endl;
	std::cout << DolphinUtil::SetIniFile("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\ansi.ini", "environment", "name", "default1") << std::endl;

	std::cout << DolphinUtil::SetIniFile("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\utf8.ini", "environment", "name1", "default2") << std::endl;
	std::cout << DolphinUtil::SetIniFile("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\utf8bom.ini", "environment", "name1", "default2") << std::endl;
	std::cout << DolphinUtil::SetIniFile("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\ansi.ini", "environment", "name1", "default2") << std::endl;

	testGet("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\utf8.ini");
	testGet("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\utf8bom.ini");
	testGet("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\ansi.ini");

	testSet("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\utf8.ini");
	testSet("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\utf8bom.ini");
	testSet("C:\\code\\ufin\\dolphin-pc\\dolphin-electron\\config\\ansi.ini");
	*/
	return 1;
}