#ifndef MessageDB_hpp
#define MessageDB_hpp


#include "sqlite3.h"
#include <iostream>
#include <vector>


class MessageDB{

private:
	sqlite3 *m_db;
	bool m_open;

public:
	struct message{
		int id;
		std::string text;
		std::string created;
		int id_receiver;
		int id_sender;
		
	};

	MessageDB();


	// não precisa de update
	bool createTableMessage();
	bool insertTableMessage(std::string text, std::string created, int id_receiver, int id_sender);
	bool removeTableMessage(int id);

	std::vector<message> selectTableMessage();
	std::vector<message> selectTableMessage(int id);

	std::vector<message> filterMessagers(int id_receiver, int id_sender);

	void closeDB();

	
};




#endif