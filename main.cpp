#include <iostream>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <nlohmann/json.hpp>

#include <fmt/core.h>
#include <fmt/format.h>

using namespace std;
using namespace AmqpClient;
using json = nlohmann::json;

/*
All pointers are boost's smart pointers, so if the "ptr_t" variable excapes the scope, all the memories are freed and the file descripters are closed automatically.
*/
int main()
{
    fmt::println("Hello from rabbit client");

    Channel::ptr_t channel = Channel::Create("localhost", 5545, "guest", "guest");
    // char szmsg[1024];

    auto consumerTag = channel->BasicConsume(
        "test",
        "CPP_WORKER",
        true,
        true, // Это автоподтверждение получения
        false,
        1);

    while (true)
    {
        auto envelope = channel->BasicConsumeMessage(consumerTag);
        auto message = envelope->Message();

        fmt::println("Message body is");
        fmt::print("{}\n", message->Body());

        auto body = json::parse(message->Body());
    }

    // try{
    //     strcpy(szmsg, "Hi I'm C++ ");
    //     BasicMessage::ptr_t msg = BasicMessage::Create();
    //     msg->Body((string)szmsg);
    //     channel->BasicPublish("", "test",  msg);
    // }
    // catch(MessageReturnedException &e){
    //     std::cout << "Message delivery error: " << e.what() << std::endl;
    // }

    return 0;
}