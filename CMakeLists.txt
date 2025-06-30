cmake_minimum_required(VERSION 3.10)

project(my_app)

find_package(Boost REQUIRED COMPONENTS chrono system)

include_directories(/usr/local/include)

find_library(SimpleAmqpClient_LIB SimpleAmqpClient PATHS /usr/local/lib REQUIRED)
find_library(Rabbitmq_LIB rabbitmq PATHS /usr/local/lib REQUIRED)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE 
    ${SimpleAmqpClient_LIB}
    ${Rabbitmq_LIB}
    Boost::chrono 
    Boost::system)