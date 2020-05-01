#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "looper.h"
#include "./../base/timestamp.h"
#include "./../base/anyone.h"
#include <functional>
#include <memory>
#include "looper.h"

namespace Vilin {

class Connection : public std::enable_shared_from_this<Connection> {
public:
	using Callback = std::function<void(const std::shared_ptr<Connection>&)>;
  using MessageCallback = std::function<void(const std::shared_ptr<Connection>&, char*, Timestamp)>;
	
	Connection(Looper* loop, int conn_sockfd, const struct sockaddr_in& local_addr, const struct sockaddr_in& peer_addr);
  ~Connection();

  // 在loop上注册事件，连接建立时调用
  void Register();

  void Send(const void* data, size_t len);
  void Send(const std::string& message);

  void Shutdown();

  // 处理事件
  void HandleRead(Timestamp t);
  void HandleWrite();
  void HandleClose();

  // 设置回调
  void SetConnectionEstablishedCB(const Callback& cb) { connection_established_cb_ = cb; }
  void SetMessageArrivalCB(const MessageCallback& cb) { message_arrival_cb_ = cb; }
  void SetReplyCompleteCB(const Callback& cb) { reply_complete_cb_ = cb; }
  void SetConnectionCloseCB(const Callback& cb) { connection_close_cb_ = cb; }
  void SetSuicideCB(const Callback& cb) { suicide_cb_ = cb; }

  const int GetFd() const { return conn_sockfd_; }

  void SetContext(const any& context) { context_ = context; }
  const any& GetContext() const { return context_; }
  any* GetMutableContext() { return &context_; }

 private:
	Looper *loop_;

	const int conn_sockfd_;
	std::shared_ptr<EventBase> conn_eventbase_;

	struct sockaddr_in local_addr_;
	struct sockaddr_in peer_addr_;

	Callback connection_established_cb_;
	MessageCallback message_arrival_cb_;
	Callback reply_complete_cb_;
	Callback connection_close_cb_;
	Callback suicide_cb_;

  // 解析上下文
  any context_;
};

}

#endif