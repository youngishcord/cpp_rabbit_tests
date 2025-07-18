cmake_minimum_required(VERSION 3.10)

project(my_app)

find_package(nlohmann_json REQUIRED)
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

add_executable(sub pubsub/sub.cpp)
target_link_libraries(sub PRIVATE 
    ${SimpleAmqpClient_LIB}
    ${Rabbitmq_LIB}
    Boost::chrono 
    Boost::system)

add_executable(pub pubsub/pub.cpp)
target_link_libraries(pub PRIVATE 
    ${SimpleAmqpClient_LIB}
    ${Rabbitmq_LIB}
    Boost::chrono 
    Boost::system)

add_executable(pingpong pingpong/pingpong.cpp)
target_link_libraries(pingpong PRIVATE 
    ${SimpleAmqpClient_LIB}
    ${Rabbitmq_LIB}
    Boost::chrono 
    Boost::system
    nlohmann_json::nlohmann_json)