#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "./../net/server.h"
#include "router.h"
#include "./../base/timestamp.h"

namespace Vilin {

class HttpParser;
class HttpRequest;
class HttpResponse;

class HttpServer
{
public:
    HttpServer(Looper* loop, int port, int thread_num = 1);

    void SetDefaultHandler(const Route::Handler& cb) { default_handler_ = cb; }

    Route::RoutePtr NewRoute() { return router_.NewRoute(); }

    void Start();

private:
    void OnConnection(const std::shared_ptr<Connection>& conn);
    void OnMessage(const std::shared_ptr<Connection>& conn, char* buf, Timestamp t);
    void OnRequest(const std::shared_ptr<Connection>& conn, const HttpRequest& request);
    void OnClose(const std::shared_ptr<Connection>& conn);

    Server server_;
    // 默认处理函数
    Route::Handler default_handler_;
    // 分发路由
    Router router_;
};

}

#endif // HTTP_SERVER_H