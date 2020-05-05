#include <iostream>
#include "./base/help.h"
	/*
  LOG_INFO(Vilin::Singleton<Vilin::Logger>::instance()) << "info";
  LOG_DEBUG(Vilin::Singleton<Vilin::Logger>::instance()) << "debug";
  LOG_WARN(Vilin::Singleton<Vilin::Logger>::instance()) << "warn";
  LOG_ERROR(Vilin::Singleton<Vilin::Logger>::instance()) << "ERROR";

  Vilin::Looper l;
  Vilin::Server s(&l, 8000);
  s.Start();
  */

int main()
{
	
  Vilin::Looper loop;
  Vilin::HttpServer s(&loop, 8000);

  s.NewRoute()
  ->SetPath("/news/list")
  ->SetQuery("offset", "{offset:[0-9]+}")
  ->SetQuery("count", "{count:[0-9]+}")
  ->SetHeader("Connection", "keep-alive")
  ->SetHandler(getNewsList);

  s.NewRoute()
  ->SetPath("/news/content")
  ->SetQuery("id", "{id:.{24}}")
  ->SetHeader("Connection", "keep-alive")
  ->SetHandler(MyHandler);
  
  s.NewRoute()
  ->SetPath("/user")
  ->SetQuery("name", "{name:[0-9]+}")
  ->SetHeader("Connection", "keep-alive")
  ->SetHandler(userHandler);

  s.Start();
  
  /*
	Vilin::DataBase myDataBase;
	if(myDataBase.init("127.0.0.1", "root", "111111", "webServer")) {
		std::cout << "init success" << std::endl;
	} else {
		return -1;
	}
	//myDataBase.exeSQL("select id, name, phone from webServer.users");

	myDataBase.initDataBase();
	*/
}
