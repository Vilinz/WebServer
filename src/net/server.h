#ifndef SERVER_H_
#define SERVER_H_

#include <sys/socket.h>
#include "./../logger/logger.h"
#include "./../singleton/singleton.h"
#include "epoller.h"
#include <memory>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

namespace Vilin {
	class Server {
	private:
		struct sockaddr_in addr;
		int listen_fd;
	public:
		Server() {};
		void Socket();
		void Bind();
		void Listen();

		int setUp();
		void start();

		int getFd() const;
	};
}

#endif