#ifndef LOOPER_H_
#define LOOPER_H_
#include <vector>
#include <thread>
#include "epoller.h"
#include "./../base/timestamp.h"

namespace Vilin {

class Looper {
private:
	bool quit;
	const std::thread::id threadId;
	std::unique_ptr<Epoller> epoller;
public:
	Looper();
	~Looper();
	void start();
	void setQuit();

	void addEventBase(std::shared_ptr<EventBase> eventBase) {
		epoller->add(eventBase);
	}
	void modEventBase(std::shared_ptr<EventBase> eventBase) {
		epoller->mod(eventBase);
	}
	void delEventBase(std::shared_ptr<EventBase> eventBase) {
		epoller->del(eventBase);
	}

	bool isInBaseThread() const {
		return threadId == std::this_thread::get_id();
	}
};

}

#endif