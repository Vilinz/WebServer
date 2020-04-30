#include "looper.h"

namespace Vilin {

Looper::Looper() :
    quit_(false),
    thread_id_(std::this_thread::get_id()),
    epoller_(new Epoller())
{
}

Looper::~Looper() {}

// 开始循环
void Looper::Start()
{
    std::vector<std::shared_ptr<EventBase>> active_eventbase_list;

    while (!quit_)
    {
        active_eventbase_list.clear();
        active_eventbase_list = epoller_->poll();
        for (auto& it : active_eventbase_list)
        {
            it->HandleEvent();
        }
    }
}


// 运行Task，可由其他线程调用
void Looper::RunTask(Task&& task)
{
    task();
}


}