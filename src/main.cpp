#include <iostream>
#include "singleton/singleton.h"
#include "logger/logger.h"
#include "net/epoller.h"
#include "net/server.h"
#include "http/httpServer.h"
#include "http/httpRequest.h"
#include "mysql/database.h"
	/*
  LOG_INFO(Vilin::Singleton<Vilin::Logger>::instance()) << "info";
  LOG_DEBUG(Vilin::Singleton<Vilin::Logger>::instance()) << "debug";
  LOG_WARN(Vilin::Singleton<Vilin::Logger>::instance()) << "warn";
  LOG_ERROR(Vilin::Singleton<Vilin::Logger>::instance()) << "ERROR";

  Vilin::Looper l;
  Vilin::Server s(&l, 8000);
  s.Start();
  */



void MyHandler(const Vilin::HttpRequest& request, std::unordered_map<std::string, std::string>& match_map, Vilin::HttpResponse* response)
{
    response->SetStatusCode(Vilin::HttpResponse::OK);
    response->SetStatusMessage("OK");
    response->SetContentType("application/json");

    std::string body = "{\"key\":\"value\", \"age\":15}";
    response->AddHeader("Content-Length", std::to_string(body.size()));
    response->AppendHeaderToBuffer();
    response->AppendBodyToBuffer(body);
}

void userHandler(const Vilin::HttpRequest& request, std::unordered_map<std::string, std::string>& match_map, Vilin::HttpResponse* response) {
	response->SetStatusCode(Vilin::HttpResponse::OK);
  response->SetStatusMessage("OK");
  response->SetContentType("application/json");

  std::string body = "{\"name\":\"Vilin\", \"age\":20, \"height\":180}";
  response->AddHeader("Content-Length", std::to_string(body.size()));
  response->AppendHeaderToBuffer();
  response->AppendBodyToBuffer(body);
}

int main()
{
	/*
  Vilin::Looper loop;
  Vilin::HttpServer s(&loop, 8000);

  s.NewRoute()
  ->SetPath("/path/{name:[a-zA-Z]+}")
  ->SetQuery("query", "t")
  ->SetHeader("Connection", "keep-alive")
  ->SetHandler(MyHandler);
  
  s.NewRoute()
  ->SetPath("/user/{name:[a-zA-Z]+}")
  ->SetHeader("Connection", "keep-alive")
  ->SetHandler(userHandler);

  s.Start();
  */
	Vilin::DataBase myDataBase;
	if(myDataBase.init("127.0.0.1", "root", "111111", "webServer")) {
		std::cout << "init success" << std::endl;
	} else {
		return -1;
	}
	//myDataBase.exeSQL("select id, name, phone from webServer.users");

	myDataBase.initDataBase();
}
