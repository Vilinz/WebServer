#include "epoller.h"

namespace Vilin {
void Epoller::create() {
	epollFd = epoll_create(10);
	if(epollFd == -1) {
		LOG_ERROR(Singleton<Logger>::instance()) << "epoll_create error";
		exit(-1);
	}
}

void Epoller::addListenFd() {
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = listenFd;
	if(epoll_ctl(epollFd, EPOLL_CTL_ADD, listenFd, &ev) == -1) {
		LOG_ERROR(Singleton<Logger>::instance()) << "epoll_ctl error";
		exit(-1);
	}
}

void Epoller::wait() {
	for(;;) {
		int nfds = epoll_wait(epollFd, events, MAX_EVENTS, -1);
		if(nfds == -1) {
			LOG_ERROR(Singleton<Logger>::instance()) << "epoll_pwait error";
			exit(-1);
		}

		for(int n = 0; n < nfds; n++) {
			if(events[n].data.fd == listenFd) {
				struct sockaddr_in local = {};
				socklen_t addrLen = sizeof(local);
				int connFd = accept(listenFd, (struct sockaddr*)&local, &addrLen);
				cout << "client connnet" << endl;

				if(connFd == -1) {
					LOG_ERROR(Singleton<Logger>::instance()) << "accept error";
					exit(-1);
				}
				// setnonblocking(connFd);
				struct epoll_event ev;
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = connFd;
				if(epoll_ctl(epollFd, EPOLL_CTL_ADD, connFd, &ev) == -1) {
					LOG_ERROR(Singleton<Logger>::instance()) << "epoll_ctl error";
					exit(-1);
				}
			} else {
				cout << "connect" << endl;
			}
		}
	}
}
}