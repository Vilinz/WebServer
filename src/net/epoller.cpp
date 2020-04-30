#include "epoller.h"
#include "./../logger/logger.h"

namespace Vilin {
	// epoll_wait最多监听事件数
const int EVENTS_NUM = 4096;
// epoll_wait超时时间,这里是10秒
const int EPOLL_WAIT_TIME = 10000;

Epoller::Epoller() : epollFd(epoll_create1(EPOLL_CLOEXEC)), activeEvents(EVENTS_NUM) {
	if(epollFd < 0) {
		LOG_ERROR(Singleton<Logger>::instance()) << "create epoll failed";
	}
}

Epoller::~Epoller() {
	close(epollFd);
}

void Epoller::add(std::shared_ptr<EventBase> eventBase) {
	int fd = eventBase->GetFd();
	struct epoll_event event;
	event.events = eventBase->GetEvents();
	event.data.fd = fd;

	//fd2EventBaseList[fd] = eventBase;
	if(epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &event) < 0) {
		LOG_ERROR(Singleton<Logger>::instance()) << "epoll_ctl add failed";
		return;
	}
	fd2EventBaseList[fd] = eventBase;
}

void Epoller::mod(std::shared_ptr<EventBase> eventBase) {
	int fd = eventBase->GetFd();
	struct epoll_event event;
	event.events = eventBase->GetEvents();
	event.data.fd = fd;

	if(epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &event) < 0) {
		LOG_ERROR(Singleton<Logger>::instance()) << "epoll_ctl mod failed";
		fd2EventBaseList.erase(fd);
	}
}

void Epoller::del(std::shared_ptr<EventBase> eventBase) {
	int fd = eventBase->GetFd();
	struct epoll_event event;
	event.events = eventBase->GetEvents();
	event.data.fd = fd;

	if(epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, &event) < 0) {
		LOG_ERROR(Singleton<Logger>::instance()) << "epoll_ctl del failed";
	}
	fd2EventBaseList.erase(fd);
}

std::vector<std::shared_ptr<EventBase>> Epoller::poll() {
	int activeEventCount = epoll_wait(epollFd, &*activeEvents.begin(), activeEvents.size(), EPOLL_WAIT_TIME);

	if(activeEventCount < 0) {
		LOG_ERROR(Singleton<Logger>::instance()) << "epoll_wait error";
	}

	std::vector<std::shared_ptr<EventBase>> activeEventBaseList;
	for(int i = 0; i < activeEventCount; i++) {
		std::shared_ptr<EventBase> eventBase = fd2EventBaseList[activeEvents[i].data.fd];
		eventBase->SetRevents(activeEvents[i].events);

		activeEventBaseList.push_back(eventBase);
	}
	return activeEventBaseList;
}

}