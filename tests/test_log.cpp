#include "dpsys/log.h"
#include <iostream>

int main(int argc, char** argv) {
    dpsys::Logger::ptr log = dpsys::Logger::ptr( new dpsys::Logger("system") );

    DPSYS_LOG_INFO(log, "this is info message");
    DPSYS_LOG_WARN(log, "This is warnning message");

    auto FileAppender = dpsys::LogAppender::ptr( new dpsys::FileLogAppender("./system.log") );
    log->addAppender(FileAppender);
    
    DPSYS_LOG_WARN(log, "After add file appender");
    //DPSYS_LOG_ERROR(log, "This is error message");

    auto logger = dpsys::LoggerMgr::getInstance()->getLogger("system");
    DPSYS_LOG_WARN(logger, "This is message from logger manager!");
    
    return 0;
}
