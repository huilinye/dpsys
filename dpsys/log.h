#pragma once

#include <memory>
#include <vector>
#include <stdarg.h>
#include <sstream>
#include <fstream>

namespace dpsys {

#define DPSYS_LOG(logger, level, fmt, ...) \
    dpsys::LogEvent(logger, level, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
    

#define DPSYS_LOG_INFO(logger, fmt, ...) DPSYS_LOG(logger, dpsys::LogLevel::Level::INFO, fmt, ##__VA_ARGS__)
#define DPSYS_LOG_DEBUG(logger, fmt, ...) DPSYS_LOG(logger, dpsys::LogLevel::Level::DEBUG, fmt, ##__VA_ARGS__)
#define DPSYS_LOG_WARN(logger, fmt, ...) DPSYS_LOG(logger, dpsys::LogLevel::Level::WARN, fmt, ##__VA_ARGS__)
#define DPSYS_LOG_ERROR(logger, fmt, ...) DPSYS_LOG(logger, dpsys::LogLevel::Level::ERROR, fmt, ##__VA_ARGS__)

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

class Logger;
    
class LogEvent {
public:
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char* file, int line, const char* fmt, ...);
    ~LogEvent();
    std::stringstream& getSS() { return m_ss; }
private:
    std::shared_ptr<Logger> m_logger;
    LogLevel::Level m_level;
    std::stringstream m_ss;
};

class LogAppender {

public:
    typedef std::shared_ptr<LogAppender> ptr;
    
    virtual ~LogAppender() {}

    virtual void log(LogLevel::Level level, LogEvent& event) = 0;
    
};

class StdOutLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<StdOutLogAppender> ptr;
    StdOutLogAppender() {}
    void log(LogLevel::Level level, LogEvent& event) override;
    
};

class FileLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const char* file_name = "system.log");
    void log(LogLevel::Level level, LogEvent& event) override;
private:
    const char* m_fileName;
    std::ofstream m_of;
    
};

class Logger {
public:
    typedef std::shared_ptr<Logger> ptr;
    Logger();
    void log(LogLevel::Level level, LogEvent& event);
    void addAppender(LogAppender::ptr newAppender);
private:
    std::vector<LogAppender::ptr> m_appender;
    LogLevel::Level m_level;
    
};
    
}
