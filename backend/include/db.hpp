#include "sqlite3.h"
#include <iostream>
#include <vector>




class Database{

private:
	sqlite3 *m_db;
	bool m_open;


public:
	struct user{
		int id;
		std::string username;
		std::string email;
	};


	bool createTableUser();
	bool insertTableUser(std::string username, std::string email);

	std::vector<user> selectTableUser();


	Database();
	
	void closeDB();

};