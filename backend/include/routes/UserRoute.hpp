#ifndef UserRoute_hpp
#define UserRoute_hpp

#include <iostream>
#include "UserDB.hpp"
#include "crow.h"



void UserHandleLISTandPOST(crow::SimpleApp& app);
void UserHandleGETandPUTandDELETE(crow::SimpleApp& app);


#endif // UserRoute_hpp