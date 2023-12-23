#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "sqlite3.h"
#include "crow.h"
#include "db.hpp"

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


int main(int argc, char const *argv[])
{
	crow::SimpleApp app;
	
	if (argc > 1){
        cout << argv[1] << "\n";
        if (strcmp( argv[1], "createtables") == 0){
            Database *data = new Database();
            data->createTableUser();
            data->closeDB();

            delete data;

            cout << "Tables Created" << "\n";
        }
    }

	CROW_ROUTE(app, "/")([](){
		std::string paths = "paths = "
		"[\n\n  "
		"user/\n  user/<int>\n  "
		"\n\n]";
		return paths;
	});


	CROW_ROUTE(app, "/user").methods("GET"_method, "POST"_method)([](const crow::request& req){
		if (req.method == "POST"_method){
            
           	auto x = crow::json::load(req.body);
            if(!x){
            	return crow::response(400);
            }

            

            Database *data = new Database();
            bool posted = data->insertTableUser(x["username"].s(), x["email"].s());
            data->closeDB();
            delete data;

            if(posted){
            	return crow::response(200, "OK");
            }else{
            	return crow::response(400, "Error, Check input data");
            }



        }else if(req.method == "GET"_method){
        	crow::json::wvalue x;
			Database *data = new Database();
			int contador = 0;

			for (auto user : data->selectTableUser()){
				x[contador]["id"] = user.id;
				x[contador]["username"] = user.username;
				x[contador]["email"] = user.email;	

				++contador;
			}

			delete data;
			
			return crow::response(x);
        	
        }

		

	});


	

	app.port(18080).run();

	return 0;
}
