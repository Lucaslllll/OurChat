#include "db.hpp"



Database::Database(){
	int rc = sqlite3_open("sqldata.db", &m_db);
	if(rc != SQLITE_OK){
		m_open = false;
	}else{
		m_open = true;
	}


}




bool Database::insertTableUser(std::string username, std::string email){
	char* messageError;
	sqlite3_stmt *stmt;

	std::string query = "SELECT * FROM USER ORDER BY ID DESC LIMIT 1;";

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

 	std::string sql = "INSERT INTO USER VALUES("+std::to_string(id_c+1)+", '"+username+"', '"+email+"');";

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


bool Database::createTableUser(){
	std::string sql = "CREATE TABLE USER("
					  "ID INT PRIMARY KEY	NOT NULL,"
					  "USERNAME 	TEXT	NOT NULL,"
					  "EMAIL		TEXT 	NOT NULL);";
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


std::vector <Database::user> Database::selectTableUser(){
	sqlite3_stmt *stmt;
	int rc = sqlite3_open("sqldata.db", &m_db);
	std::string query = "SELECT * FROM USER;";
	std::vector<user> vector_users;

	rc = sqlite3_prepare_v2(m_db, query.c_str(), query.length(), &stmt, nullptr);
	if (rc != SQLITE_OK){
		std::cerr << "Erro no SELECT \n";
		return vector_users;
	}

	while((rc = sqlite3_step(stmt)) == SQLITE_ROW){
		user users;

		users.id = sqlite3_column_int(stmt, 0);
		users.username = (const char*)sqlite3_column_text(stmt, 1);
		users.email = (const char*)sqlite3_column_text(stmt, 2);

		vector_users.push_back(users);	

	}

	sqlite3_finalize(stmt);

	return vector_users;

}


void Database::closeDB(){
	sqlite3_close(m_db);
}
