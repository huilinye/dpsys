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

LogEvent::LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char* file, int line, const char* fmt, ...)
    :m_logger(logger)
    ,m_level(level){
    // Write time format
    struct tm tm;
    time_t now = time(0);
    localtime_r(&now, &tm);
    char buf[64];
    std::string time_format = "%Y-%m-%d %H:%M:%S \t";
    strftime(buf, sizeof(buf), time_format.c_str(), &tm);
    m_ss << buf;

    // Write file and line info
    std::string temp(file);
    auto begin = temp.rfind("/");
    std::string file_name = temp.substr(begin+1);
    m_ss<<file_name<<":"<<line<<"\t";
    // Write log level format
    m_ss<<std::string(LogLevel::ToString(level))<<"\t|\t";

    // Write log message
    va_list argptr;
    va_start(argptr, fmt);
    char* str = nullptr;
    int len = vasprintf(&str, fmt, argptr);
    if( len != -1) {
        m_ss<<std::string(str, len)<<std::endl;
        free(str);
    }
    va_end(argptr);
    //std::cout<<m_ss.str();
    //logger.log(level, *this);
}

LogEvent::~LogEvent() {
    m_logger->log(m_level, *this);

}

Logger::Logger(std::string name)
    :m_level(LogLevel::Level::DEBUG)
    ,m_name(name) {
    m_appender.push_back(LogAppender::ptr(new StdOutLogAppender())); //default std::cout appender
}
        
void Logger::log(LogLevel::Level level, LogEvent& event){
    if( level >= m_level) {
        for(auto i : m_appender) {
            i->log(level, event);
        }
        if(level >= LogLevel::ERROR) {
            throw std::runtime_error("Abort due to error!");
        }
        
    }
    
}

void Logger::addAppender(LogAppender::ptr newAppender) {
    m_appender.push_back(newAppender);
}

void StdOutLogAppender::log(LogLevel::Level level, LogEvent& event) {
    std::cout<<event.getSS().str();
}

FileLogAppender::FileLogAppender(const char* file_name)
    :m_fileName(file_name){}
    
void FileLogAppender::log(LogLevel::Level level, LogEvent& event) {
    if(m_of.is_open()){
        m_of<<event.getSS().str();
        m_of.close();
    } else {
        m_of.open(m_fileName);
        m_of<<event.getSS().str();
        m_of.close();
    }
}


LogManager::LogManager() {
    Logger::ptr root = Logger::ptr( new Logger("root") );
    m_loggers[root->getName()] = root;
};

Logger::ptr LogManager::getLogger(std::string key) {
    auto it = m_loggers.find(key);
    if( it != m_loggers.end()) {
        return it->second;
    }

    Logger::ptr newLogger = Logger::ptr( new Logger(key) );
    m_loggers[newLogger->getName()] = newLogger;
    return newLogger;
}

    
}  // namesapce dpsys
