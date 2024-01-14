#include "MessageRoute.hpp"


void MessageHandleLISTandPOST(crow::SimpleApp& app){
	CROW_ROUTE(app, "/message").methods("GET"_method, "POST"_method)([](const crow::request& req){
		if (req.method == "POST"_method){
            
           	auto x = crow::json::load(req.body);
            if(!x){
            	return crow::response(400);
            }

            

            MessageDB *data = new MessageDB();
            bool posted = data->insertTableUser(x["text"].s(), x["created"].s(), x["id_receiver"].i(), x["id_sender"].i());
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


void MessageHandleGETandPUTandDELETE(crow::SimpleApp& app){

}