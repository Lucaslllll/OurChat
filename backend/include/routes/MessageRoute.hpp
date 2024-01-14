#ifndef MessageRoute_hpp
#define MessageRoute_hpp

#include <iostream>
#include "MessageDB.hpp"
#include "crow.h"



void MessageHandleLISTandPOST(crow::SimpleApp& app);
void MessageHandleGETandPUTandDELETE(crow::SimpleApp& app);


#endif