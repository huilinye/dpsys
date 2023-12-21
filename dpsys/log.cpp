#include "log.h"
#include <iostream>
#include <exception>

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
        
void Logger::log(LogLevel::Level level, std::string file_name, int line_number, const char* fmt, va_list argptr){
    if( level >= m_level) {
        for(auto i : m_appender) {
            i->log(level, file_name, line_number, fmt, argptr);
        }
        
    }
    
}

void Logger::info(std::string file_name, int line_number, const char* fmt, ...) {
    va_list argptr;
    va_start(argptr, fmt);
    log(LogLevel::INFO, file_name, line_number, fmt, argptr);
    va_end(argptr);
}
    
void Logger::debug(std::string file_name, int line_number, const char* fmt, ...) {
    va_list argptr;
    va_start(argptr, fmt);
    log(LogLevel::DEBUG,  file_name, line_number, fmt, argptr);
    va_end(argptr);
}

void Logger::warn(std::string file_name, int line_number, const char* fmt, ...){
    va_list argptr;
    va_start(argptr, fmt);
    log(LogLevel::WARN,  file_name, line_number, fmt, argptr);
    va_end(argptr);
}

void Logger::error(std::string file_name, int line_number, const char* fmt, ...) {
    va_list argptr;
    va_start(argptr, fmt);
    log(LogLevel::ERROR, file_name, line_number, fmt, argptr);
    va_end(argptr);
    throw std::runtime_error("Abort due to error!");
}



void write_format(std::ostream& ofs, LogLevel::Level level, std::string file_name, int line_number, const char* fmt, va_list argptr) {
    
    char* str = nullptr;
    int len = vasprintf(&str, fmt, argptr);
    if( len != -1) {

        // Write time format
        struct tm tm;
        time_t now = time(0);
        localtime_r(&now, &tm);
        char buf[64];
        std::string time_format = "%Y-%m-%d %H:%M:%S \t";
        strftime(buf, sizeof(buf), time_format.c_str(), &tm);
        ofs << buf;

        // Write file and line info
        auto begin = file_name.rfind("/");
        std::string file = file_name.substr(begin+1);
        ofs<<file<<":"<<line_number<<"\t";
        // Write log level format
        ofs<<std::string(LogLevel::ToString(level))<<"\t|\t";

        // Write log message
        ofs<<std::string(str, len)<<std::endl;
        free(str);
    }
}

void StdOutLogAppender::log(LogLevel::Level level, std::string file_name, int line_number, const char* fmt, va_list argptr) {
    write_format(std::cout, level, file_name, line_number, fmt, argptr);
}

}  // namesapce dpsys
