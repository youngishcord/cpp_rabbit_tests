#include <iostream>
#include <SimpleAmqpClient/SimpleAmqpClient.h>

using namespace std;
using namespace AmqpClient;

/*
All pointers are boost's smart pointers, so if the "ptr_t" variable excapes the scope, all the memories are freed and the file descripters are closed automatically.
*/


const auto QUEUE_NAME = "test";

int main(int argc, char * argv[])
{
    std::cout << "test message" << "\n";
    
	// создание подключения
	Channel::ptr_t channel = Channel::Create("localhost", 5672, "user", "pass");

	channel->DeclareQueue(QUEUE_NAME, false, true, false, false);

	auto message = AmqpClient::BasicMessage::Create("Test message");
	channel->BasicPublish("", QUEUE_NAME, message, true, false);

	std::cout << "Message sended: " << message << std::endl;
    
    return 0;

}