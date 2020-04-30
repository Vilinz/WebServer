#include <iostream>
#include "singleton/singleton.h"
#include "logger/logger.h"
#include "net/epoller.h"
#include "net/server.h"

int main() {
  LOG_INFO(Vilin::Singleton<Vilin::Logger>::instance()) << "info";
  LOG_DEBUG(Vilin::Singleton<Vilin::Logger>::instance()) << "debug";
  LOG_WARN(Vilin::Singleton<Vilin::Logger>::instance()) << "warn";
  LOG_ERROR(Vilin::Singleton<Vilin::Logger>::instance()) << "ERROR";

  //Vilin::Server s;
  //s.start();
  return 0;
}
