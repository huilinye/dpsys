#include "log.h"
#include <iostream>


namespace dpsys{

const char* LogLevel::ToString(LogLevel::Level level) {
    switch(level) {
#define XX(name) \
    case LogLevel::name: \
        return #name; \
        break;

    XX(DEBUG);
    XX(INFO);
    XX(WARN);
    XX(ERROR);
    XX(FATAL);
#undef XX
    default:
        return "UNKNOW";
    }
    return "UNKNOW";
}

    Logger::Logger()
        :m_level(LogLevel::Level::DEBUG) {
        m_appender.push_back(LogAppender::ptr(new StdOutLogAppender())); //default std::cout appender
    }
        
void Logger::log(LogLevel::Level level, const char* fmt, va_list argptr){
    if( level >= m_level) {
        
        for(auto i : m_appender) {
            i->log(level, fmt, argptr);
        }
        
    }
    
}

void Logger::info(const char* fmt, ...) {
    va_list argptr;
    va_start(argptr, fmt);
    log(LogLevel::INFO, fmt, argptr);
    va_end(argptr);
}
    
void Logger::debug(const char* fmt, ...) {
    va_list argptr;
    va_start(argptr, fmt);
    log(LogLevel::DEBUG, fmt, argptr);
    va_end(argptr);
}

void Logger::warn(const char* fmt, ...){
    va_list argptr;
    va_start(argptr, fmt);
    log(LogLevel::WARN, fmt, argptr);
    va_end(argptr);
}

void Logger::error(const char* fmt, ...) {
    va_list argptr;
    va_start(argptr, fmt);
    log(LogLevel::ERROR, fmt, argptr);
    va_end(argptr);
}



void write_format(std::ostream& ofs, LogLevel::Level level, const char* fmt, va_list argptr) {
    
    char* str = nullptr;
    int len = vasprintf(&str, fmt, argptr);
    if( len != -1) {
        ofs<<std::string(LogLevel::ToString(level))<<"| ";
        ofs<<std::string(str, len)<<std::endl;
        free(str);
    }
}

void StdOutLogAppender::log(LogLevel::Level level, const char* fmt, va_list argptr) {
    write_format(std::cout, level, fmt, argptr);
}

}  // namesapce dpsys
