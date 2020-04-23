#include "logger.h"
#include <time.h>
#include <fstream>

void FileAppender::log(shared_ptr<LogEvent> ptr){
  ofstream outFile(name, ios::app);
  if(!outFile.is_open()) {
    cout << "Open log file error" << endl;
    return;
  }

  outFile << ptr->getTime() << "\t" << ptr->getLevel() << "\t";
  outFile << ptr->getFile() << "\t" << ptr->getLine() << "\t" << ptr->getContent() << endl;

  outFile.close();
}

void stdoutAppender::log(shared_ptr<LogEvent> ptr) {  
  cout << ptr->getTime() << "\t" << ptr->getLevel() << "\t";
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

