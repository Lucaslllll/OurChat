cmake_minimum_required(VERSION 3.5)
project("OurChat" VERSION 0.1 LANGUAGES CXX )

# set the compiling flags
set ( CMAKE_CXX_FLAGS "-Wall -g" )


### [1] Application target
# configura o diretório contendo os .h, assim você pode incluílos apenas com include "arquivo.h"
include_directories( include
					 include/routes
					 include/models
	
					)



### [2] Test engine
# includes do test manager

# Cria um executável com nome "program" com base no main.cpp
set( APP_NAME "ourchat" )
add_executable( ${APP_NAME}
                src/main.cpp
                src/models/UserDB.cpp
                src/models/MessageDB.cpp
                src/routes/UserRoute.cpp
                src/routes/MessageRoute.cpp

                
                )

# define C++14 standard
set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD 14)

#sqlite3 find
include_directories(/usr/include)
link_directories(/usr/lib)

#crow
find_package(Crow)

# json
## find_package(nlohmann_json 3.11.2 REQUIRED)

# add crow and sqlite3 and json
target_link_libraries(${APP_NAME} PUBLIC Crow::Crow sqlite3)





# The end