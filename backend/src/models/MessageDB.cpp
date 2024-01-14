#include "MessageDB.hpp"




MessageDB::MessageDB(){
	int rc = sqlite3_open("sqldata.db", &m_db);
	if(rc != SQLITE_OK){
		m_open = false;
	}else{
		m_open = true;
	}

}


// não precisa de update do crud
bool MessageDB::createTableMessage(){
	std::string sql = "CREATE TABLE MESSAGE("
					  "ID INT PRIMARY KEY	NOT NULL,"
					  "TEXT 	TEXT	NOT NULL,"
					  "CREATED		DATE 	NOT NULL,"
					  "ID_RECEIVER		INT,"
					  "ID_SENDER		INT,"
					  "FOREIGN KEY(ID_RECEIVER) REFERENCES USER(ID_RECEIVER),"
					  "FOREIGN KEY(ID_SENDER) REFERENCES USER(ID_SENDER) );";
	char* messageError;
	int exit = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &messageError);

	if(exit != SQLITE_OK){
		std::cout << messageError << '\n';
		sqlite3_free(messageError); // essa messageError só ser alocada e usada se 'sqlite3_exec' der erro
		return false;

	}else{
		return true;

	}
}

bool MessageDB::insertTableMessage(std::string text, std::string created, int id_receiver, int id_sender){
	char* messageError;
	sqlite3_stmt *stmt;

	std::string query = "SELECT * FROM MESSAGE ORDER BY ID DESC LIMIT 1;";

	int rc = sqlite3_prepare_v2(m_db, query.c_str(), query.length(), &stmt, nullptr);
	int id_c = 0;

	if(rc != SQLITE_OK){
		std::cerr << "Erro no select \n";
		sqlite3_finalize(stmt);
		return false;
 	}else{
 		while( (rc = sqlite3_step(stmt)) == SQLITE_ROW ){
 			id_c = sqlite3_column_int(stmt, 0);
 		}
 	}
 	sqlite3_finalize(stmt);

 	std::string sql = "INSERT INTO MESSAGE VALUES("+std::to_string(id_c+1)+", '"+text+"', "+created+", "+std::to_string(id_receiver)+", "+std::to_string(id_sender)+");";

 	rc = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &messageError);
 	if(rc != SQLITE_OK){
 		std::cerr << messageError << '\n';
 		sqlite3_free(messageError);

 		return false;
 	}else{
 		std::cout << "Records created Successfully!\n";
 		return true; 
 	}
}

bool MessageDB::removeTableMessage(int id){
	char* messageError;
	// int exit = sqlite3_open("sqldata.db", &m_db); m_db já é aberto no construtor

	std::string query = "DELETE FROM USER WHERE ID='"+std::to_string(id)+"';";
	int exit = sqlite3_exec(m_db, query.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK){
		std::cerr << messageError << '\n';
		sqlite3_free(messageError);

		return false;
	}else{
		std::cerr << "Records Removed Successfully \n";
		return true;
	}
}


std::vector<MessageDB::message> MessageDB::selectTableMessage(){
	sqlite3_stmt *stmt;
	// int rc = sqlite3_open("sqldata.db", &m_db); desnecessário abrir novamente, já abri no construtor
	std::string query = "SELECT * FROM MESSAGE;";
	std::vector<messages> vector_messages;

	int rc = sqlite3_prepare_v2(m_db, query.c_str(), query.length(), &stmt, nullptr);
	if (rc != SQLITE_OK){
		std::cerr << "Erro no SELECT \n";
		sqlite3_finalize(stmt);
		return vector_messages;
	}

	while((rc = sqlite3_step(stmt)) == SQLITE_ROW){
		message messages;

		messages.id = sqlite3_column_int(stmt, 0);
		messages.text = (const char*)sqlite3_column_text(stmt, 1);
		messages.created = (const char*)sqlite3_column_text(stmt, 2);
		messages.id_receiver = sqlite_column_int(stmt, 3);
		messages.id_sender = sqlite_column_int(stmt, 4);

		vector_messages.push_back(messages);	

	}

	sqlite3_finalize(stmt);

	return vector_messages;
}

std::vector<MessageDB::message> MessageDB::selectTableMessage(int id){
	sqlite3_stmt *stmt;
	// int rc = sqlite3_open("sqldata.db", &m_db); desnecessário abrir novamente, já abri no construtor
	std::string query = "SELECT * FROM MESSAGE WHERE ID='"+std::to_string(id)+"';";
	std::vector<message> vector_messages;

	int rc = sqlite3_prepare_v2(m_db, query.c_str(), query.length(), &stmt, nullptr);
	if (rc != SQLITE_OK){
		std::cerr << "Erro no SELECT \n";
		sqlite3_finalize(stmt);
		return vector_messages;
	}

	while((rc = sqlite3_step(stmt)) == SQLITE_ROW){
		message messages;

		messages.id = sqlite3_column_int(stmt, 0);
		messages.text = (const char*)sqlite3_column_text(stmt, 1);
		messages.created = (const char*)sqlite3_column_text(stmt, 2);
		messages.id_receiver = sqlite_column_int(stmt, 3);
		messages.id_sender = sqlite_column_int(stmt, 4)

		vector_messages.push_back(messages);	

	}

	sqlite3_finalize(stmt);

	return vector_messages;
}
