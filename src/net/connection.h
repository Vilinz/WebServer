#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "looper.h"

namespace Vilin {

class Connection {
private:
	Looper *loop_;

	const int connSockFd;
	std::shared_ptr<EventBase> connEventBase;

	struct sockaddr_in localAddr;
	struct sockaddr_in peerAddr;
public:
	Connection();
	~Connection();

	void register_();

	void handleRead(Timestamp t);
  void handleWrite();
  void handleClose();
};

}

#endif