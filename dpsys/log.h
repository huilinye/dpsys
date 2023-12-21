#include <memory>
#include <vector>
#include <stdarg.h>
namespace dpsys {

#define DPSYS_LOG_INFO(logger, fmt, ...) logger.info(fmt, __VA_ARGS__)
#define DPSYS_LOG_DEBUG(logger, fmt, ...) logger.debug(fmt, __VA_ARGS__)
#define DPSYS_LOG_WARN(logger, fmt, ...) logger.warn(fmt, __VA_ARGS__)
#define DPSYS_LOG_ERROR(logger, fmt, ...) logger.error(fmt, __VA_ARGS__)

class LogLevel {
public:
    enum Level {
        UNKNOWN = 0,
        INFO    = 1,
        DEBUG   = 2,
        WARN    = 3,
        ERROR   = 4,
        FATAL   = 5
    };

    static const char* ToString(Level level);
};

class LogAppender {

public:
    typedef std::shared_ptr<LogAppender> ptr;
    
    virtual ~LogAppender() {}

    virtual void log(LogLevel::Level level, const char* fmt, va_list argptr) = 0;
    
};

class StdOutLogAppender : LogAppender {
public:
    typedef std::shared_ptr<StdOutLogAppender> ptr;
    StdOutLogAppender() {}
    void log(LogLevel::Level level, const char* fmt, va_list argptr) override;
    
};


class Logger {
public:
    Logger();
    void log(LogLevel::Level level, const char* fmt, va_list argptr);
    void info(const char* fmt, ...);
    void debug(const char* fmt, ...);
    void warn(const char* fmt, ...);
    void error(const char* fmt, ...);
    
private:
    std::vector<StdOutLogAppender::ptr> m_appender;
    LogLevel::Level m_level;
    
};
    
}
