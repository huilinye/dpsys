#include "dpsys/log.h"


int main(int argc, char** argv) {
    dpsys::Logger log;

    DPSYS_LOG_INFO(log, "this is info message");
    DPSYS_LOG_WARN(log, "This is warnning message");

    auto FileAppender = dpsys::LogAppender::ptr( new dpsys::FileLogAppender("./fuck.log") );
    log.addAppender(FileAppender);
    
    DPSYS_LOG_WARN(log, "After add file appender");
    DPSYS_LOG_ERROR(log, "This is error message");
    return 0;
}
