#include "database.h"
#include "./../singleton/singleton.h"
#include "./../logger/logger.h"
#include <jsoncpp/json/json.h>
#include <iostream>
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

void DataBase::exeSQL(std::string sql) {
	if(mysql_query(mysql, sql.c_str())) {
		std::cout << "query error:" << mysql_error(mysql);
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
		} else {
			if(mysql_field_count(mysql) == 0) {
				int num_rows = mysql_affected_rows(mysql);
			} else {
				std::cout << "get result error:" << mysql_error(mysql);
			}
		}
	}
}

void DataBase::initDataBase() {
	ifstream is(fileName, ios::in);

	if(!is.is_open()) {
		LOG_ERROR(Singleton<Logger>::instance()) << "open json file failed";
		exit(-1);
	}

	Json::Reader reader;
	Json::Value root;

	if(reader.parse(is, root)) {
		std::cout << root[0] << std::endl;
	}

	is.close();
}

}