#include <iostream>
#include "singleton/singleton.h"
#include "logger/logger.h"
#include "net/epoller.h"
#include "net/server.h"

int main() {
  LOG_INFO(Singleton<Logger>::instance()) << "info";
  LOG_DEBUG(Singleton<Logger>::instance()) << "debug";
  LOG_WARN(Singleton<Logger>::instance()) << "warn";
  LOG_ERROR(Singleton<Logger>::instance()) << "ERROR";

  Vilin::Server s;
  s.start();
  return 0;
}
