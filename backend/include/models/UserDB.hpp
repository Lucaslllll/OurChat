#ifndef UserDB_hpp
#define UserDB_hpp


#include "sqlite3.h"
#include <iostream>
#include <vector>




class UserDB{

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
	bool insertTableUser(std::string username, std::string email, std::string password);
	bool removeTableUser(int id);
	bool updateTableUser(int id, std::string username, std::string email);


	std::vector<user> selectTableUser();
	std::vector<user> selectTableUser(int id);


	UserDB();
	
	void closeDB();

};


#endif