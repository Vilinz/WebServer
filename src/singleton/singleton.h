#include <iostream>
#include <mutex>
#include <memory>
using namespace std;

#ifndef SINGLETON_H_
#define SINGLETON_H_

template <class T>
class Singleton {
private:
  Singleton() {
    ;
  }
public:
  static mutex gMutex;
  static shared_ptr<T> instance();
};

template <class T>
mutex Singleton<T>::gMutex;

template <class T>
shared_ptr<T> Singleton<T>::instance() {
  lock_guard<mutex> _(gMutex);
  static shared_ptr<T> obj(new T());
  return obj;
}

#endif
