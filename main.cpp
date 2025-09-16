#include <iostream>
#include <memory>

#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <nlohmann/json.hpp>

#include <fmt/format.h>

#include "include/thread_queue.h"
#include "include/thread_task.h"
#include "include/worker/worker.h"

using namespace std;
using namespace AmqpClient;
using json = nlohmann::json;

/*
All pointers are boost's smart pointers, so if the "ptr_t" variable excapes the scope, all the memories are freed and the file descripters are closed automatically.
*/
int main()
{
    // Очередь, передающая структуру. TODO: возможно, нужно передавать смарт поинтеры!
    // ThreadSafeQueue<ThreadTask> taskQueue;
    auto taskQueue = std::make_shared<ThreadSafeQueue<ThreadTask>>();

    // Создание полноценного треда с воркером
    std::thread workerThread(runWorker, "localhost", 5545, "guest", "guest", taskQueue);
    workerThread.detach();

    while (true)
    {
        ThreadTask task;
        if (taskQueue->try_pop(task))
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            auto result = task.function();
            task.promise.set_value(result);
        }
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