#include <iostream>
#include <SimpleAmqpClient/SimpleAmqpClient.h>

#include <nlohmann/json.hpp>

#include <chrono>
#include <thread>

using namespace std;
using namespace AmqpClient;

/*
All pointers are boost's smart pointers, so if the "ptr_t" variable excapes the scope, all the memories are freed and the file descripters are closed automatically.
*/


const auto QUEUE_NAME = "qwer";

int main(int argc, char * argv[])
{
    // std::cout << "test message" << "\n";
    
	// создание подключения
	Channel::ptr_t channel = Channel::Create(
		"localhost", 
		5672, 
		"user", 
		"pass", 
		"/"
	);


	channel->DeclareQueue(QUEUE_NAME, false, true, false, false);

	
	auto consumer = channel->BasicConsume(QUEUE_NAME, "", true, false, false);
	std::cout << "Tag: " << consumer << std::endl;
	
	channel->BasicQos(consumer, 2);
	
	while (1) {
		
		auto envelope = channel->BasicConsumeMessage(consumer);
		std::cout << "Received " << envelope->Message()->Body() << std::endl;
		std::cout << "Routing key " << envelope->RoutingKey() << std::endl;
		// std::cout << "Delivery info " << envelope-> << std::endl;
		// Я ХЗ ОТКУДЯ МНЕ ДОСТАТЬ ИМЯ ЗАДАЧИ
		
		
		// std::this_thread::sleep_for(std::chrono::seconds(1));
		
		std::cout << "success" << std::endl;
		
		channel->BasicAck(envelope);
	}
	
    return 0;

}