#ifndef UTIL_LOG_H_
#define UTIL_LOG_H_

#include <string>

typedef enum LOGGER_LEVEL
{
    TrackLevel      = 0,
    InLevel         = 1,
    OutLevel        = 2,
    InfoLevel       = 3,
    WarningLevel    = 4,
    ErrorLevel      = 5,
    FatalLevel      = 6,
    DisableLevel    = 99,
} ENM_LOGGER_LEVEL;

class Log
{
public:
    Log(const std::string& strFilePath, const std::string& strFunctionName, int iLine);
    ~Log();
public:
    static void Write(ENM_LOGGER_LEVEL logLevel, 
        const std::string& strFilePath, 
        const std::string& strFunctionName, 
        int iLine,
        const char* pszFormat, ...);
public:
    static FILE* CreateLogFile();
    static int CheckLogFileEnabled();
    static std::string GetShortFuncName(const std::string& strFunctionName);
    static std::string GetLevel(ENM_LOGGER_LEVEL logLevel);
private:
    const std::string      m_strFilePath;
    const std::string      m_strFunctionName;
    int                    m_iLine;
};

#define LTRACE(formatstr, ...)      Log::Write(TrackLevel,    (__FILE__), (__FUNCTION__), __LINE__, formatstr, ##__VA_ARGS__)
#define LINFO(formatstr, ...)       Log::Write(InfoLevel,     (__FILE__), (__FUNCTION__), __LINE__, formatstr, ##__VA_ARGS__)

#define LWARNING(formatstr, ...)                                                                            \
            do                                                                                                  \
            {                                                                                                   \
                Log::Write(WarningLevel, (__FILE__), (__FUNCTION__), __LINE__, formatstr, ##__VA_ARGS__);   \
            } while (false)

#define LERROR(formatstr, ...)                                                                              \
            do                                                                                                  \
            {                                                                                                   \
                Log::Write(ErrorLevel, (__FILE__), (__FUNCTION__), __LINE__, formatstr, ##__VA_ARGS__);     \
            } while (false)

#define LFATAL(formatstr, ...)                                                                              \
            do                                                                                                  \
            {                                                                                                   \
                Log::Write(FatalLevel, (__FILE__), (__FUNCTION__), __LINE__, formatstr, ##__VA_ARGS__);     \
            } while (false)

#define LOGOUT(level, formatstr, ...)                                                                       \
            do                                                                                                  \
            {                                                                                                   \
                Log::Write(level, (__FILE__), (__FUNCTION__), __LINE__, formatstr, ##__VA_ARGS__);           \
                if (WarningLevel == level || ErrorLevel == level || FatalLevel == level)                        \
                {                                                                                               \
                }                                                                                               \
            } while (false)

#define LOGGER                      Log __tmp_logger__((__FILE__), (__FUNCTION__), __LINE__)

#endif
