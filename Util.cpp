#include <string>
#include <time.h>
#include "SimpleIni.h"


#ifdef _WIN32
//#undef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace DolphinUtil {
    // Directory Operations

    std::string GetModuleFile(){

#if defined(_WIN32)
    char tszModule[MAX_PATH + 1] = { 0 };
    ::GetModuleFileNameA(NULL, tszModule, MAX_PATH);
    return std::string(tszModule);
#elif defined(__linux__)
        char buffer[2048] = {0};
        int nCount = readlink("/proc/self/exe", buffer, 2048);
        if (nCount < 0 || nCount >= 2048){
            return "";
        }
        return std::string(buffer);
#else
    return "";
#endif
    }

    std::string GetModuleName() {
        std::string path = DolphinUtil::GetModuleFile();
        auto idx = path.find_last_of("\\"); // windows style
        if (idx == std::string::npos) {
            idx = path.find_last_of("/"); // linux style
        }

        if (idx == std::string::npos) {
            return path;
        }

        return path.substr(idx+1, path.size() - idx);
    }

    std::string GetModuleFileDir(){
        std::string path = DolphinUtil::GetModuleFile();
        auto idx = path.find_last_of("\\"); // windows style
        if(idx == std::string::npos){
            idx = path.find_last_of("/"); // linux style
        }

        if (idx == std::string::npos) {
            return path;
        }

        return path.substr(0, idx);
    }

    std::string GetCacheDir(){
        std::string modulePath = GetModuleFileDir();
        return modulePath + "/../cache/";
    }

    std::string GetCurrentPID() {
#ifdef _WIN32
        DWORD dwPID = ::GetCurrentProcessId();
        CHAR szTmp[16] = { 0 };
        ::sprintf_s(szTmp, _countof(szTmp), ("%ld"), dwPID);
        return szTmp;
#else
        int pid = getpid();
        return std::to_string(pid);
#endif
    }

    std::string GetCurrentTID() {
#ifdef _WIN32
        DWORD dwPID = ::GetCurrentThreadId();
        CHAR szTmp[16] = { 0 };
        ::sprintf_s(szTmp, _countof(szTmp), ("%ld"), dwPID);
        return szTmp;
#else
        int tid = gettid();
        return std::to_string(tid);
#endif
    }

    std::string GetDateTimeString(std::string format /*= "%m-%d %H:%M:%S"*/) {
        time_t t = time(NULL);
        char ch[64] = { 0 };
        strftime(ch, sizeof(ch) - 1, format.c_str(), localtime(&t));
        return std::string(ch);
    }

    bool IsDirExists(std::string path) {
#ifdef _WIN32
        DWORD dwAttrib = GetFileAttributesA(path.c_str());
        return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
#else
        struct stat sb;
        if (stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)){
            return true;
        }
        return false;
#endif
    }

    bool CreateDir(std::string path) {
#ifdef _WIN32
        BOOL bRet = ::CreateDirectoryA(path.c_str(), NULL);
        if (FALSE == bRet){
            DWORD dwLastErr = ::GetLastError();
            if(ERROR_ALREADY_EXISTS !=  dwLastErr) return false;
        }
        return true;
#else
        int status = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        if (-1 == status){
            return false;
        }
        return true;
#endif
    }

    bool DelFile(std::string path) {
#ifdef _WIN32
        return (bool) DeleteFileA(path.c_str());
#else
       return 0 == remove(path.c_str());
#endif
    }

    // Ini file operations
    bool SetIniFile(std::string path, std::string section, std::string key, std::string value){
#ifdef _WIN32
    return WritePrivateProfileStringA(section.c_str(), key.c_str(), value.c_str(), path.c_str());
#else
    CSimpleIniA ini;
    SI_Error rc = ini.LoadFile(path.c_str());
    if (rc < 0) return false;

    rc = ini.SetValue(section.c_str(), key.c_str(), value.c_str());
    if (rc < 0) return false;

    rc = ini.SaveFile(path.c_str());
    if (rc < 0) return false;

    return true;
#endif
    }

    std::string GetIniFileString(std::string path, std::string section, std::string key, std::string defautValue){
#ifdef _WIN32
    char buff[1024] = {0};
    GetPrivateProfileStringA(section.c_str(), key.c_str(), defautValue.c_str(), buff, 1024, path.c_str());
    return std::string(buff);
#else
    CSimpleIniA ini;
    SI_Error rc = ini.LoadFile(path.c_str());
    if (rc < 0) return defautValue;

    const char* v = ini.GetValue(section.c_str(), key.c_str(), defautValue.c_str());

    // remove ""
    std::string s(v);
    if (s.size() > 0 && s[0] == '"') {
        s = s.substr(1);
    }

    if (s.size() > 0 && s[s.size()-1] == '"') {
        s = s.substr(0, s.size()-1);
    }

    return s;
#endif
    }

    int GetIniFileInt(std::string path, std::string section, std::string key, int defautValue) { 
#ifdef _WIN32
        return GetPrivateProfileIntA(section.c_str(), key.c_str(), defautValue, path.c_str());
#else
        CSimpleIniA ini;
        SI_Error rc = ini.LoadFile(path.c_str());
        if (rc < 0) return defautValue;

        return ini.GetLongValue(section.c_str(), key.c_str(), defautValue);
#endif
    }

    bool GetIniFileBool(std::string path, std::string section, std::string key, bool defautValue) {
        std::string defaultString = defautValue ? "true" : "false";
        std::string value = GetIniFileString(path, section, key, defaultString);

        if (value == "true") return true;
        if (value == "false") return false;

        return defautValue;
    }
}