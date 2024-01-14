#include "UserDB.hpp"



UserDB::UserDB(){
	int rc = sqlite3_open("sqldata.db", &m_db);
	if(rc != SQLITE_OK){
		m_open = false;
	}else{
		m_open = true;
	}


}

bool UserDB::createTableUser(){
	std::string sql = "CREATE TABLE USER("
					  "ID INT PRIMARY KEY	NOT NULL,"
					  "USERNAME 	TEXT	NOT NULL,"
					  "EMAIL		TEXT 	NOT NULL,"
					  "PASSWORD		TEXT	NOT NULL);";
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


bool UserDB::insertTableUser(std::string username, std::string email, std::string password){
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

 	std::string sql = "INSERT INTO USER VALUES("+std::to_string(id_c+1)+", '"+username+"', '"+email+"', '"+password+"');";

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


bool UserDB::removeTableUser(int id){
	char* messageError;
	// int exit = sqlite3_open("sqldata.db", &m_db); já é aberto no construtor

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


bool UserDB::updateTableUser(int id, std::string username, std::string email){
	char* messageError;

	std::string query = "UPDATE USER SET USERNAME='"+username+"', EMAIL='"+email+"' WHERE ID='"+std::to_string(id)+"';";
	int exit = sqlite3_exec(m_db, query.c_str(), NULL, 0, &messageError);

	if(exit != SQLITE_OK){
		std::cerr << messageError << '\n';
		sqlite3_free(messageError);
		return false;
	}else{
		std::cerr << "USER updated Successfully! \n";
		return true;
	}
}



std::vector <UserDB::user> UserDB::selectTableUser(){
	sqlite3_stmt *stmt;
	// int rc = sqlite3_open("sqldata.db", &m_db); desnecessário abrir novamente, já abri no construtor
	std::string query = "SELECT * FROM USER;";
	std::vector<user> vector_users;

	int rc = sqlite3_prepare_v2(m_db, query.c_str(), query.length(), &stmt, nullptr);
	if (rc != SQLITE_OK){
		std::cerr << "Erro no SELECT \n";
		sqlite3_finalize(stmt);
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

std::vector <UserDB::user> UserDB::selectTableUser(int id){
	sqlite3_stmt *stmt;
	// int rc = sqlite3_open("sqldata.db". &m_db); desnecessário abrir novamente, já foi aberto no construtor
	std::string query = "SELECT * FROM USER WHERE ID='"+std::to_string(id)+"';";
	std::vector<user> vector_users;

	int rc = sqlite3_prepare_v2(m_db, query.c_str(), query.length(), &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Error in query or other unknown error" << '\n';
		sqlite3_finalize(stmt);

		return vector_users;
	}

	while((rc = sqlite3_step(stmt)) == SQLITE_ROW){
		user u;

		u.id = sqlite3_column_int(stmt, 0);
		u.username = (const char*)sqlite3_column_text(stmt, 1);
		u.email = (const char*)sqlite3_column_text(stmt, 2);

		vector_users.push_back(u);
	}


	sqlite3_finalize(stmt);

	return vector_users;

}


void UserDB::closeDB(){
	sqlite3_close(m_db);
}
