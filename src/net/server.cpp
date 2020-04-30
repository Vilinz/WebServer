#include "server.h"

namespace Vilin {
void Server::Socket() {
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(listen_fd == -1) {
		LOG_ERROR(Singleton<Logger>::instance()) << "socket error";
		exit(-1);
	}
}

void Server::Bind() {
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(listen_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		LOG_ERROR(Singleton<Logger>::instance()) << "bing error";
		exit(-1);
	}
}

void Server::Listen() {
	if(listen(listen_fd, 5) == -1) {
		LOG_ERROR(Singleton<Logger>::instance()) << "listen error";
		exit(-1);
	}
}

int Server::setUp() {
	Socket();
	Bind();
	Listen();
	return listen_fd;
}

void Server::start() {
	setUp();
	Epoller epoller(listen_fd);
	epoller.create();
	epoller.addListenFd();
	epoller.wait();
}

int Server::getFd() const {
	return listen_fd;
}

}