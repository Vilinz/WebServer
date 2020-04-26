#include <sys/epoll.h>
#include "./../logger/logger.h"
#include "./../singleton/singleton.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef EPOLLER_H_
#define EPOLLER_H_

namespace Vilin {
class Epoller {
private:
	int listenFd;
	int epollFd;
	enum COUNT {
		MAX_EVENTS = 10
	};
	struct epoll_event events[MAX_EVENTS];
public:
	Epoller(int listenFd_) : listenFd(listenFd_) {};
	void create();
	void addListenFd();
	void wait();
};
}

#endif