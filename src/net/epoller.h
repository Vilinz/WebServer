#ifndef EPOLLER_H_
#define EPOLLER_H_

#include <sys/epoll.h>
#include "./../logger/logger.h"
#include "./../singleton/singleton.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include "eventBase.h"
#include <vector>
#include <memory>
#include <map>

class EventBase;

namespace Vilin {

class Epoller {
private:
	int epollFd;
	std::vector<epoll_event> activeEvents;
	std::map<int, std::shared_ptr<EventBase>> fd2EventBaseList;
public:
	Epoller();
	~Epoller();
	void add(std::shared_ptr<EventBase> eventBase);
	void mod(std::shared_ptr<EventBase> eventBase);
	void del(std::shared_ptr<EventBase> eventBase);

	std::vector<std::shared_ptr<EventBase>> poll();
};

}

#endif