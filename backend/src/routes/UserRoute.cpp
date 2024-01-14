#include "UserRoute.hpp"


void UserHandleLISTandPOST(crow::SimpleApp& app){
	CROW_ROUTE(app, "/user").methods("GET"_method, "POST"_method)([](const crow::request& req){
		if (req.method == "POST"_method){
            
           	auto x = crow::json::load(req.body);
            if(!x){
            	return crow::response(400);
            }

            

            UserDB *data = new UserDB();
            bool posted = data->insertTableUser(x["username"].s(), x["email"].s(), x["password"].s());
            data->closeDB();
            delete data;

            if(posted){
            	return crow::response(200, "OK");
            }else{
            	return crow::response(400, "Error, Check input data");
            }



        }else if(req.method == "GET"_method){
        	crow::json::wvalue x;
			UserDB data = UserDB();
			int contador = 0;

			for (auto user : data.selectTableUser()){
				x[contador]["id"] = user.id;
				x[contador]["username"] = user.username;
				x[contador]["email"] = user.email;	

				++contador;
			}
            data.closeDB();
			
			return crow::response(x);
        	
        }

		
		return crow::response(405, "method not accept");        
	});
}



void UserHandleGETandPUTandDELETE(crow::SimpleApp& app){
    CROW_ROUTE(app, "/user/<int>").methods("DELETE"_method, "PUT"_method, "GET"_method)([](const crow::request& req, int id){
        if(req.method == "DELETE"_method){
            auto x = crow::json::load(req.body);
            if (!x){
                return crow::response(400);
            }

            UserDB data = UserDB();
            bool deleted = data.removeTableUser(id);
            data.closeDB();
            

            if (deleted){
                return crow::response(200, "deleted with success");
            }else{
                return crow::response(404, "not found task");
            }

            
        }else if(req.method == "PUT"_method){
            auto x = crow::json::load(req.body);
            if (!x){
                return crow::response(400);
            }

            UserDB data = UserDB();
            bool updated = data.updateTableUser(id, x["username"].s(), x["email"].s());
            data.closeDB();

            if (updated){
                return crow::response(200, "ok");
            }else{
                return crow::response(400, "ID not exist or missing data in form");
            }


        }else if(req.method == "GET"_method){
            // UserDB *data = new UserDB(); usar a stack é mais rápido do que usar heap, o objeto vai morrer automática depois desse escopo 
            // nesse caso só armazenar na stack vai ser mais apropriado para meu objetivo
            UserDB data = UserDB();
            crow::json::wvalue x;
            int contador = 0;

            for (auto user : data.selectTableUser(id)){
                x[contador]["id"] = user.id;
                x[contador]["username"] = user.username;
                x[contador]["email"] = user.email;

                ++contador;

            }
            data.closeDB();

            return crow::response(x);

        }


        return crow::response(405, "method not accept");

    });
}