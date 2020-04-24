#include <iostream>
#include "singleton/singleton.h"
#include "logger/logger.h"


//shared_ptr<Logger> logger(shared_ptr<Logger>(new Logger("my_logger", DEBUG)));
shared_ptr<Logger> logger = Singleton<Logger>::instance();
int main() {
  logger->addAppender(shared_ptr<LogAppender>(new stdoutAppender("app")));
  logger->addAppender(shared_ptr<LogAppender>(new FileAppender("fileAppender", "log")));
  LOG_INFO(logger) << "info";
  LOG_DEBUG(logger) << "debug";
  LOG_WARN(logger) << "warn";
  LOG_ERROR(logger) << "ERROR";
  return 0;
}
