#include <iostream>
#include "logger/logger.h"

int main() {
  Logger *logger = new Logger("my_logger", Level(0));
  logger->addAppender(shared_ptr<LogAppender>(new stdoutAppender("app")));
  logger->log(shared_ptr<LogEvent>(new LogEvent(1, Level(1), "f",23,"Hello")));
  return 0;
}
