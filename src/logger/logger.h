#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
using namespace std;

#ifndef LOGGER_H_
#define LOGGER_H_


#define VILIN_LOG(logger, level) \
  if(logger->getLevel() <= level) \
    LogEventWarp(shared_ptr<LogEvent>(new LogEvent(logger, time(0), level, __FILE__, __LINE__))).getSS()

#define LOG_INFO(logger) VILIN_LOG(logger, INFO)
#define LOG_DEBUG(logger) VILIN_LOG(logger, DEBUG)
#define LOG_WARN(logger) VILIN_LOG(logger, WARN)
#define LOG_ERROR(logger) VILIN_LOG(logger, ERROR)

enum Level {
  INFO,
  DEBUG,
  WARN,
  ERROR
};


class Logger;

class LogEvent {
private:
  uint64_t time;
  Level level;
  string file;
  uint32_t line;
  stringstream content;
  shared_ptr<Logger> ptr;
public:
  LogEvent(shared_ptr<Logger> p, uint64_t t, Level l, string f, uint32_t line_, string c):ptr(p), time(t), level(l), file(f), line(line_), content(c){}
  
  LogEvent(shared_ptr<Logger> p, uint64_t t, Level l, string f, uint32_t line_):ptr(p), time(t), level(l), file(f), line(line_){}
  
  uint64_t getTime() const {
    return time;
  }

  Level getLevel() const {
    return level;
  }

  string getFile() const {
    return file;
  }

  uint32_t getLine() const {
    return line;
  }

  string getContent() const {
    return content.str();
  }

  shared_ptr<Logger> getLogger() {
    return ptr;
  }

  stringstream& getSS() {
    return content;
  }
};

class LogEventWarp {
private:
  shared_ptr<LogEvent> ptr;
public:
  LogEventWarp(shared_ptr<LogEvent> p) {
    ptr = p;
  }
  ~LogEventWarp();
  stringstream& getSS() {
    return ptr->getSS();
  }
};

class LogAppender {
protected:
  string name;
public:
  LogAppender(string n):name(n){

  }
  
  string getName() const {
    return name;
  }

  virtual void log(shared_ptr<LogEvent> ptr) = 0;
};

class FileAppender : public LogAppender {
private:
  string file_name;
public:
  FileAppender(string f, string n):file_name(f), LogAppender(n) {

  }
  void log(shared_ptr<LogEvent> ptr) override;
};

class stdoutAppender : public LogAppender {
public:
  stdoutAppender(string n):LogAppender(n){

  };
  void log(shared_ptr<LogEvent> ptr) override;
};

class Logger{
private:
  string name;
  vector<shared_ptr<LogAppender>> appenders;
  Level level;
public:
  Logger() : name("defaultLogger"), level(INFO) {
    addAppender(shared_ptr<LogAppender>(new stdoutAppender("app")));
    addAppender(shared_ptr<LogAppender>(new FileAppender("fileAppender", "log")));
  }

  Logger(string n, Level l) : name(n), level(l) {
    addAppender(shared_ptr<LogAppender>(new stdoutAppender("app")));
    addAppender(shared_ptr<LogAppender>(new FileAppender("fileAppender", "log")));
  }

  string getName() const {
    return name;
  }

  Level getLevel() {
    return level;
  }

  void addAppender(shared_ptr<LogAppender> ptr);

  void delAppenderByName(string name);

  void log(shared_ptr<LogEvent> ptr);
};

#endif
