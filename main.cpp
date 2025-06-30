#include <iostream>
#include <SimpleAmqpClient/SimpleAmqpClient.h>

using namespace std;
using namespace AmqpClient;

/*
All pointers are boost's smart pointers, so if the "ptr_t" variable excapes the scope, all the memories are freed and the file descripters are closed automatically.
*/
int main(int argc, char * argv[])
{
    // std::cout << "test message" << "\n";
    Channel::ptr_t channel = Channel::Create("localhost", 5672, "user", "pass");
    char szmsg[1024];

    try{
        strcpy(szmsg, "Hi I'm C++ ");
        BasicMessage::ptr_t msg = BasicMessage::Create();
        msg->Body((string)szmsg);
        channel->BasicPublish("", "SampleQueue",  msg);
    }
    catch(MessageReturnedException &e){
        std::cout << "Message delivery error: " << e.what() << std::endl;
    }

    
    return 0;

}