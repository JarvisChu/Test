//#include "define.h"
#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include <iostream>
#include "Util.h"

#ifdef _WIN32
#include <windows.h>
#endif

#define LOG_FLAG_UNKNOWN   0 // 未知，需要检查配置文件来确定
#define LOG_FLAG_SAVE2FILE 1 // 日志需要存盘
#define LOG_FLAG_NO_SAVE   2 // 日志不需要存盘

static FILE* g_fpLogFile = NULL; // 日志文件指针
static int   g_nLogFlag = 0;     // 是否需要写日志的标记，取值：LOG_FLAG_XXX

void onExitClean()
{
    if (NULL != g_fpLogFile){
        fclose(g_fpLogFile);
        g_fpLogFile = NULL;
    }
}

//#define LOGGER_LEVEL_NOW DisableLevel
#define LOGGER_LEVEL_NOW TrackLevel

Log::Log(const std::string& strFilePath, const std::string& strFunctionName, int iLine)
    : m_strFilePath(strFilePath)
    , m_strFunctionName(strFunctionName)
    , m_iLine(iLine)
{
    Log::Write(InLevel, m_strFilePath, m_strFunctionName, m_iLine, (""));
}

Log::~Log()
{
    Log::Write(OutLevel, m_strFilePath, m_strFunctionName, m_iLine, (""));
}

void Log::Write(ENM_LOGGER_LEVEL logLevel,
    const std::string& strFilePath,
    const std::string& strFunctionName,
    int iLine,
    const char* pszFormat, ...)
{
    //log level filter
    if (LOGGER_LEVEL_NOW > logLevel) {
        return;
    }

    std::string strModuleName = ("[#");
    strModuleName.append(Util::GetModuleName());
    strModuleName.append(("#]"));

    std::string strPidAndTid = ("[");
    strPidAndTid.append(Util::GetCurrentPID());
    strPidAndTid.append((", "));
    strPidAndTid.append(Util::GetCurrentTID());
    strPidAndTid.append(("]"));

    std::string strDateTime = Util::GetDateTimeString();

    const size_t nLogBufferLength = 14 * 4096;
    char szLog[nLogBufferLength] = { 0 };

    int nCount = std::snprintf(szLog, nLogBufferLength, ("%-14s %-24s %-8s %-48s ")
        , strPidAndTid.c_str()
        , strDateTime.c_str()
        , GetLevel(logLevel).c_str()
        , GetShortFuncName(strFunctionName).c_str());


    if (nCount < 0 || static_cast<size_t>(nCount) >= nLogBufferLength){
        return;
    }

    va_list ap;
    va_start(ap, pszFormat);
    nCount += std::vsnprintf(szLog + static_cast<size_t>(nCount), nLogBufferLength - static_cast<size_t>(nCount), pszFormat, ap);
    va_end(ap);

    if (nCount < 0 || static_cast<size_t>(nCount) >= nLogBufferLength){
        return;
    }

    nCount += std::snprintf(szLog + static_cast<size_t>(nCount), nLogBufferLength - static_cast<size_t>(nCount), ("\n"));

    std::cout << szLog << std::endl;

    // 检查是否需要写日志文件
    if( g_nLogFlag == LOG_FLAG_UNKNOWN){
        g_nLogFlag = CheckLogFileEnabled();
    }

    // 不需要写日志文件
    if( g_nLogFlag == LOG_FLAG_NO_SAVE){ 
        return;
    }

    // 其它情况，均默认为需要写日志文件
    if (NULL == g_fpLogFile){
        std::atexit(onExitClean);
        g_fpLogFile = CreateLogFile();
    }

    if (NULL != g_fpLogFile){
        fputs(szLog, g_fpLogFile);
        fflush(g_fpLogFile);
    }
}

FILE* Log::CreateLogFile()
{
    std::string cacheDir = Util::GetCacheDir();
    std::string logDir = cacheDir + "/logs/";

    if (!Util::IsDirExists(logDir)) {
        if (!Util::CreateDir(logDir)) {
            return NULL;
        }
    }

    std::string path = logDir
        + "electron_core_"
        + Util::GetDateTimeString("%Y_%m_%d_%H_%M_%S") + "_"
        + Util::GetCurrentPID() + ".txt";

    FILE* f = fopen(path.c_str(), "wb+");
    return f;
}

// 检查是否开启了日志，默认是为开启
int Log::CheckLogFileEnabled()
{
    std::string path = Util::GetModuleFileDir();
    path += "/resources/configs.ini";

    // 默认为日志需要存盘
    bool bRet = Util::GetIniFileBool(path, "environment", "electron_log", true);
    return bRet ? LOG_FLAG_SAVE2FILE : LOG_FLAG_NO_SAVE;
}

std::string Log::GetShortFuncName(const std::string& strFunctionName)
{
    // 只包含类名和函数名

    if (strFunctionName.size() <= 2)
    {
        return strFunctionName;
    }

    std::size_t index1 = strFunctionName.rfind(("::"));
    if (std::string::npos == index1)
    {
        return strFunctionName;
    }
    else
    {
        std::size_t index2 = strFunctionName.rfind(("::"), 0 == index1 ? 0 : index1 - 1);
        return (std::string::npos == index2 ? strFunctionName : strFunctionName.substr(index2 + 2));
    }
}

std::string Log::GetLevel(ENM_LOGGER_LEVEL logLevel)
{
    if (InLevel == logLevel)           return (("[IN]"));
    else if (OutLevel == logLevel)     return (("[OUT]"));
    else if (TrackLevel == logLevel)   return (("[T]"));
    else if (InfoLevel == logLevel)    return (("[I]"));
    else if (WarningLevel == logLevel) return (("[W]"));
    else if (ErrorLevel == logLevel)   return (("[E]"));  
    else if (FatalLevel == logLevel)   return (("[F]"));  
    else return ("");
}
