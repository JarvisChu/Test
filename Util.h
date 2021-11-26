#ifndef DOLPHIN_UTIL_UTIL_H_
#define DOLPHIN_UTIL_UTIL_H_

#include <string>

namespace DolphinUtil {
    // Directory Operations
    std::string GetModuleFile();
    std::string GetModuleName();
    std::string GetModuleFileDir();
    std::string GetCacheDir();
    std::string GetCurrentPID();
    std::string GetCurrentTID();
    std::string GetDateTimeString(std::string format = "%m-%d %H:%M:%S");
    bool IsDirExists(std::string path);
    bool CreateDir(std::string path);
    bool DelFile(std::string path);

    // Ini file operations
    bool SetIniFile(std::string path, std::string section, std::string key, std::string value);
    std::string GetIniFileString(std::string path, std::string section, std::string key, std::string defautValue);
    int GetIniFileInt(std::string path, std::string section, std::string key, int defautValue);
    bool GetIniFileBool(std::string path, std::string section, std::string key, bool defautValue);
}

#endif // DOLPHIN_UTIL_UTIL_H_