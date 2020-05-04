#include "database.h"
#include "./../singleton/singleton.h"
#include "./../logger/logger.h"
#include <jsoncpp/json/json.h>
#include <iostream>
#include <cstring>
#include <fstream>

namespace Vilin {

DataBase::DataBase() : fileName("./data/newsData.json") {
	mysql = mysql_init(nullptr);
	if(mysql == nullptr) {
		std::cout << "error:" << mysql_error(mysql);
		exit(1);
	}
}

DataBase::~DataBase() {
	if(mysql) {
		mysql_close(mysql);
	}
}

bool DataBase::init(std::string i, std::string u, std::string pwd, std::string dbName) {
	mysql = mysql_real_connect(mysql, i.c_str(), u.c_str(), pwd.c_str(), dbName.c_str(), 0, nullptr, 0);
	if(!mysql) {
		std::cout << "error:" << mysql_error(mysql);
		exit(1);
	}
	return true;
}

bool DataBase::exeSQL(std::string sql) {
	if(mysql_query(mysql, sql.c_str())) {
		std::cout << "query error:" << mysql_error(mysql);
		return false;
	} else {
		MYSQL_RES *result = mysql_store_result(mysql);
		if(result) {
			int num_fields = mysql_num_fields(result);
			int num_rows = mysql_num_rows(result);
			for(int i = 0; i < num_rows; i++) {
				MYSQL_ROW row = mysql_fetch_row(result);
				if(row < 0) {
					break;
				}
				for(int j = 0; j < num_fields; j++) {
					std::cout << row[j] << "\t";
				}
				std::cout << std::endl;
			}
			if(num_rows <= 0) {
				LOG_ERROR(Singleton<Logger>::instance()) << "empty query";
				return false;
			}
			return true;
		} else {
			if(mysql_field_count(mysql) == 0) { //非查询语句
				int num_rows = mysql_affected_rows(mysql);
				if(num_rows > 0) {
					return true;
				} else {
					return false;
				}
			} else {
				std::cout << "get result error:" << mysql_error(mysql);
				return false;
			}
		}
	}
}

void DataBase::initDataBase() {

	if(exeSQL("select group_id from webServer.news where group_id='6rpn/L5K52HooGQp9PZ/gA=='")) {
		LOG_INFO(Singleton<Logger>::instance()) << "data had been insert";
		return;
	}

	ifstream is(fileName, ios::in);

	if(!is.is_open()) {
		LOG_ERROR(Singleton<Logger>::instance()) << "open json file failed";
		exit(-1);
	}

	Json::Reader reader;
	Json::Value root;

	if(reader.parse(is, root)) {
		LOG_INFO(Singleton<Logger>::instance()) << "news adding into database...";
		
		for(int i = 0; i < root.size(); i++) {
			/*
			string image_infos = "";
			for(int j = 0; j < root[i][0]["image_infos"].size(); j++) {
				image_infos += root[i][0]["image_infos"][j]["height"].asString() + "|_|";
				image_infos += root[i][0]["image_infos"][j]["width"].asString() + "|_|";
				image_infos += root[i][0]["image_infos"][j]["image_type"].asString() + "|_|";
				image_infos += root[i][0]["image_infos"][j]["mime_type"].asString() + "|_|";
				image_infos += root[i][0]["image_infos"][j]["url_prefix"].asString() + "|_|";
				image_infos += root[i][0]["image_infos"][j]["web_uri"].asString();
				if(j != root[i][0]["image_infos"].size() - 1) {
					image_infos += "|+|";
				}
			}
			*/
			
			char content[10240];
			mysql_real_escape_string(mysql, content, root[i][0]["title"].asString().c_str(), strlen(root[i][0]["title"].asString().c_str()));

			char image_infos[10000];
			mysql_real_escape_string(mysql, image_infos, root[i][0]["image_infos"].toStyledString().c_str(), strlen(root[i][0]["image_infos"].toStyledString().c_str()));
			
			string s = "insert into webServer.news (group_id, title, image_infos, content) values (\"" + root[i][0]["group_id"].asString() +
									"\",\"" + root[i][0]["title"].asString() + "\",\"" + image_infos + "\",\"" + content + "\")";
			if(!exeSQL(s)) {
				LOG_ERROR(Singleton<Logger>::instance()) << "insert news error";
			}
			
		}
		LOG_INFO(Singleton<Logger>::instance()) << "news added into database";
	}

	is.close();
}

}