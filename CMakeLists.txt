cmake_minimum_required(VERSION 3.22)

project(my_app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/json-3.12.0)
find_package(nlohmann_json REQUIRED)

find_package(Boost REQUIRED COMPONENTS chrono system)

add_subdirectory(lib/rabbitmq-c)
set(rabbitmq-c_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../rabbitmq-c)
set(rabbitmq-c_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../rabbitmq-c/librabbitmq)
set(rabbitmq-c_LIBRARY rabbitmq)

add_subdirectory(lib/SimpleAmqpClient)
# find_package(SimpleAmqpClient REQUIRED)

add_subdirectory(lib/fmt)

include_directories(include)

add_executable(my_app main.cpp)
target_include_directories(my_app PUBLIC include)
target_link_libraries(my_app PRIVATE 
    SimpleAmqpClient
    rabbitmq
    Boost::chrono 
    Boost::system
    nlohmann_json::nlohmann_json
    fmt::fmt)

# add_executable(sub pubsub/sub.cpp)
# target_link_libraries(sub PRIVATE 
#     ${SimpleAmqpClient_LIB}
#     ${Rabbitmq_LIB}
#     Boost::chrono 
#     Boost::system
#     fmt::fmt)

# add_executable(pub pubsub/pub.cpp)
# target_link_libraries(pub PRIVATE 
#     ${SimpleAmqpClient_LIB}
#     ${Rabbitmq_LIB}
#     Boost::chrono 
#     Boost::system
#     fmt::fmt)

# add_executable(pingpong pingpong/pingpong.cpp)
# target_link_libraries(pingpong PRIVATE 
#     ${SimpleAmqpClient_LIB}
#     ${Rabbitmq_LIB}
#     Boost::chrono 
#     Boost::system
#     nlohmann_json::nlohmann_json
#     fmt::fmt)