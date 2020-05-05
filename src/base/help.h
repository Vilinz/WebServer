#ifndef HELP_H_
#define  HELP_H_

#include "./../singleton/singleton.h"
#include "./../logger/logger.h"
#include "./../net/epoller.h"
#include "./../net/server.h"
#include "./../http/httpServer.h"
#include "./../http/httpRequest.h"
#include "./../mysql/database.h"

#include "./../rapidjson/document.h"
#include "./../rapidjson/writer.h"
#include "./../rapidjson/stringbuffer.h"

#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <memory>
using namespace std;

shared_ptr<Vilin::DataBase> database = Vilin::Singleton<Vilin::DataBase>::instance();

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

void getNewsList(const Vilin::HttpRequest& request, std::unordered_map<std::string, std::string>& match_map, Vilin::HttpResponse* response) {
	response->SetStatusCode(Vilin::HttpResponse::OK);
  response->SetStatusMessage("OK");
  response->SetContentType("application/json");

  string offset = request.GetQuery("offset");
  string count = request.GetQuery("count");
 
  string sql = "SELECT group_id, title, image_infos " \
								"FROM webServer.news " \
								"ORDER BY group_id " \
								"LIMIT " + count + " OFFSET " + offset;
  MYSQL_RES* result = database->querySQL(sql);
  int num_fields = mysql_num_fields(result);
	int num_rows = mysql_num_rows(result);

	if(num_rows <= 0) {
		LOG_ERROR(Vilin::Singleton<Vilin::Logger>::instance()) << "empty query";
		return;
	}
	
	rapidjson::StringBuffer stringBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(stringBuffer);
	
	writer.StartObject();
	writer.Key("data");
	writer.StartArray();
	
	for(int i = 0; i < num_rows; i++) {
		writer.StartObject();
		MYSQL_ROW row = mysql_fetch_row(result);
		if(row < 0) {
			break;
		}
		writer.Key("group_id");
		writer.String(static_cast<string>(row[0]).c_str());
		writer.Key("title");
		writer.String(static_cast<string>(row[1]).c_str());
		writer.Key("image_infos");
		writer.StartArray();
		rapidjson::Document d;
		d.Parse(static_cast<string>(row[2]).c_str());
		d.Accept(writer);
		//writer.String(static_cast<string>(row[2]).c_str());
		writer.EndArray();
		writer.EndObject();
	}
	writer.EndArray();
	writer.EndObject();
	
	string body = stringBuffer.GetString();
	response->AddHeader("Content-Length", std::to_string(body.size()));
  response->AppendHeaderToBuffer();
  response->AppendBodyToBuffer(body);
}

#endif