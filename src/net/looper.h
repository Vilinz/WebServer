#ifndef LOOPER_H_
#define LOOPER_H_
#include <vector>
#include <unistd.h>
#include <mutex>
#include <thread>
#include <memory>
#include <functional>
#include "epoller.h"
#include "./../base/timestamp.h"

namespace Vilin {

class EventBase;

class Looper
{
public:
    using Task = std::function<void()>;

    Looper();
    ~Looper();
    
    // 开始事件循环
    void Start();
    // 退出循环，由其他线程调用
    void Quit() { quit_ = true; }

    // 注册事件
    void AddEventBase(std::shared_ptr<EventBase> eventbase) { epoller_->add(eventbase); }
    void ModEventBase(std::shared_ptr<EventBase> eventbase) { epoller_->mod(eventbase); }
    void DelEventBase(std::shared_ptr<EventBase> eventbase) { epoller_->del(eventbase); }


    void RunTask(Task&& task);

private:
    // 退出标识
    bool quit_;


    // 该loop所在线程id
    const std::thread::id thread_id_;

    std::unique_ptr<Epoller> epoller_;
};

}

#endif