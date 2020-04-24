#include "logger.h"
#include <time.h>
#include <fstream>

LogEventWarp::~LogEventWarp(){
  ptr->getLogger()->log(ptr);
}
void FileAppender::log(shared_ptr<LogEvent> ptr){
  ofstream outFile(name, ios::app);
  if(!outFile.is_open()) {
    cout << "Open log file error" << endl;
    return;
  }

  string lelInfo;
  switch(ptr->getLevel()) {
    case INFO:
      lelInfo = "info";
      break;
    case DEBUG:
      lelInfo = "debug";
      break;
    case WARN:
      lelInfo = "warn";
      break;
    case ERROR:
      lelInfo = "error";
      break;
    default:
      break;
  }
  
  string m_format = "%Y-%M-%D %H:%M:%S";
  struct tm tm;
  time_t time = ptr->getTime();
  localtime_r(&time, &tm);
  char buf[64];
  strftime(buf, sizeof(buf), m_format.c_str(), &tm);

  outFile << buf << "\t" << lelInfo << "\t";
  outFile << ptr->getFile() << "\t" << ptr->getLine() << "\t" << ptr->getContent() << endl;

  outFile.close();
}

void stdoutAppender::log(shared_ptr<LogEvent> ptr) {  
  string lelInfo;
  switch(ptr->getLevel()) {
    case INFO:
      lelInfo = "info";
      break;
    case DEBUG:
      lelInfo = "debug";
      break;
    case WARN:
      lelInfo = "warn";
      break;
    case ERROR:
      lelInfo = "error";
      break;
    default:
      break;
  }
  string m_format = "%Y-%M-%D %H:%M:%S";
  struct tm tm;
  time_t time = ptr->getTime();
  localtime_r(&time, &tm);
  char buf[64];
  strftime(buf, sizeof(buf), m_format.c_str(), &tm);
  cout << buf << "\t" << lelInfo << "\t";
  cout << ptr->getFile() << "\t" << ptr->getLine() << "\t" << ptr->getContent() << endl;
}

void Logger::addAppender(shared_ptr<LogAppender> ptr) {
  appenders.push_back(ptr);
}

void Logger::delAppenderByName(string name) {
  for(auto it = appenders.begin(); it != appenders.end(); it++) {
    if((*it)->getName() == name) {
      appenders.erase(it);
      break;
    }
  }
}

void Logger::log(shared_ptr<LogEvent> ptr) {
  if(ptr->getLevel() >= level) {
    for(int i = 0; i < appenders.size(); i++) {
      appenders[i]->log(ptr);
    }
  }
}

