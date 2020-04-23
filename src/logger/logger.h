#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

#ifndef LOGGER_H_
#define LOGGER_H_
enum Level {
  INFO,
  DEBUG,
  WARN,
  ERROR
};

class LogEvent {
private:
  uint32_t time;
  Level level;
  string file;
  uint32_t line;
  string content;
public:
  LogEvent(uint32_t t, Level l, string f, uint32_t line_, string c):time(t), level(l), file(f), line(line_), content(c){}
  
  uint32_t getTime() const {
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
    return content;
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
  Logger(string n, Level l) : name(n), level(l) {

  }

  string getName() const {
    return name;
  }

  void addAppender(shared_ptr<LogAppender> ptr);

  void delAppenderByName(string name);

  void log(shared_ptr<LogEvent> ptr);
};

#endif
