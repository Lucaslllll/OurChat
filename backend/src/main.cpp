#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "sqlite3.h"
#include "crow.h"

#include "UserRoute.hpp"
#include "UserDB.hpp"

#include "MessageRoute.hpp"
#include "MessageDB.hpp"

using namespace std;


static int callback(void* data, int argc, char** argv, char** azColName){
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;

}

void HandleWithDB(int argc, char const *argv[]){
    if (argc > 1){
        cout << argv[1] << "\n";
        if (strcmp( argv[1], "createtables") == 0){
            UserDB *data = new UserDB();
            data->createTableUser();
            data->closeDB();
            delete data;

            MessageDB *data2 = new MessageDB();
            data2->createTableMessage();
            data2->closeDB();
            delete data2;

            cout << "Tables Created" << "\n";
        }else if(strcmp( argv[1], "sqlmanipulation") == 0){
            // MANIPULATION AND TESTING


            cout << "to exit type /q" << "\n";
            sqlite3 *m_db;
            char* messageError;
            string query = "";
            bool looping = true;
            int exit = sqlite3_open("sqldata.db", &m_db);

            // update


            while(looping == true){
                getline(cin, query);

                if (query == "/q"){
                    looping = false;
                }else{


                    exit = sqlite3_exec(m_db, query.c_str(), callback, 0, &messageError);
                    if (exit != SQLITE_OK) {
                        cerr << messageError << "\n";
                        sqlite3_free(messageError);

                    }


                }


            }

            // ia me esquecendo de fechar
            sqlite3_free(messageError);
            sqlite3_close(m_db);
        }

    }
}

void URLsSHOW(crow::SimpleApp& app){
    CROW_ROUTE(app, "/")([](){
        std::string paths = "paths = "
        "[\n\n  "
        "user/\n  user/<int>\n  "
        "message/\n message/<int>\n"
        "\n\n]";
        return paths;
    });
}




int main(int argc, char const *argv[]){

	crow::SimpleApp app;
    

    HandleWithDB(argc, argv);	
    URLsSHOW(app);


	// routes User
	UserHandleLISTandPOST(app);
	UserHandleGETandPUTandDELETE(app);
	

    // routes Message
    MessageHandleLISTandPOST(app);
    MessageHandleGETandDELETE(app);
    MessageHandleFILTER(app);


    // Rota WebSocket para o chat
    
	

	app.port(18090).run();

	return 0;
}
