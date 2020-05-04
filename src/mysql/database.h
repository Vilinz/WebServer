#ifndef DATABASE_H_
#define DATABASE_H_

#include <iostream>
#include <string>
#include <mysql/mysql.h>

namespace Vilin {

class DataBase {
public:
	DataBase();
	~DataBase();

	bool init(std::string i, std::string u, std::string pwd, std::string dbName);

	void initDataBase();

	bool hadInsert(std::string sql);

	bool exeSQL(std::string sql);
private:
	std::string ip;
	std::string user;
	std::string password;
	std::string dataBaseName;
	MYSQL *mysql;
	std::string fileName;
};

}

#endif