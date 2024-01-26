#include "MessageRoute.hpp"


void MessageHandleLISTandPOST(crow::SimpleApp& app){
	CROW_ROUTE(app, "/message").methods("GET"_method, "POST"_method)([](const crow::request& req){
		if (req.method == "POST"_method){
            
           	auto x = crow::json::load(req.body);
            if(!x){
            	return crow::response(400);
            }

            

            MessageDB *data = new MessageDB();
            bool posted = data->insertTableMessage(x["text"].s(), x["created"].s(), x["id_receiver"].i(), x["id_sender"].i());
            data->closeDB();
            delete data;

            if(posted){
            	return crow::response(200, "OK");
            }else{
            	return crow::response(400, "Error, Check input data");
            }



        }else if(req.method == "GET"_method){
        	crow::json::wvalue x;
			MessageDB data = MessageDB();
			int contador = 0;

			for (auto message : data.selectTableMessage()){
				x[contador]["id"] = message.id;
				x[contador]["text"] = message.text;
				x[contador]["created"] = message.created;	
				x[contador]["id_receiver"] = message.id_receiver;
				x[contador]["id_sender"] = message.id_sender;

				++contador;
			}
            data.closeDB();
			
			return crow::response(x);
        	
        }

		
		return crow::response(405, "method not accept");        
	});


}


void MessageHandleGETandDELETE(crow::SimpleApp& app){
	CROW_ROUTE(app, "/message/<int>").methods("DELETE"_method, "PUT"_method, "GET"_method)([](const crow::request& req, int id){
        if(req.method == "DELETE"_method){
            auto x = crow::json::load(req.body);
            if (!x){
                return crow::response(400);
            }

            MessageDB data = MessageDB();
            bool deleted = data.removeTableMessage(id);
            data.closeDB();
            

            if (deleted){
                return crow::response(200, "deleted with success");
            }else{
                return crow::response(404, "not found message");
            }

            
        }else if(req.method == "GET"_method){
            // MessageDB *data = new MessageDB(); usar a stack é mais rápido do que usar heap, o objeto vai morrer automática depois desse escopo 
            // nesse caso só armazenar na stack vai ser mais apropriado para meu objetivo
            MessageDB data = MessageDB();
            crow::json::wvalue x;
            int contador = 0;

            for (auto message : data.selectTableMessage(id)){
                x[contador]["id"] = message.id;
                x[contador]["text"] = message.text;
                x[contador]["created"] = message.created;
                x[contador]["id_receiver"] = message.id_receiver;
                x[contador]["id_sender"] = message.id_sender;

                ++contador;

            }
            data.closeDB();

            return crow::response(x);

        }


        return crow::response(405, "method not accept");

    });
}


void MessageHandleFILTER(crow::SimpleApp& app){
    CROW_ROUTE(app, "/message/<int>/<int>").methods("GET"_method, "POST"_method)([](const crow::request& req, int id_receiver, int id_sender){
        if(req.method == "GET"_method){
            // MessageDB *data = new MessageDB(); usar a stack é mais rápido do que usar heap, o objeto vai morrer automática depois desse escopo 
            // nesse caso só armazenar na stack vai ser mais apropriado para meu objetivo
            MessageDB data = MessageDB();
            crow::json::wvalue x;
            int contador = 0;

            for (auto message : data.filterMessagers(id_receiver, id_sender)){
                x[contador]["id"] = message.id;
                x[contador]["text"] = message.text;
                x[contador]["created"] = message.created;
                x[contador]["id_receiver"] = message.id_receiver;
                x[contador]["id_sender"] = message.id_sender;

                ++contador;

            }
            data.closeDB();

            return crow::response(x);

        }


        return crow::response(405, "method not accept");

    });

}