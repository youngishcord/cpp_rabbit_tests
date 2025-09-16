#include <memory>
#include <string>

#include <fmt/base.h>
#include <fmt/format.h>

#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <nlohmann/json.hpp>

#include <thread_queue.h>
#include <thread_task.h>

using namespace std;
using namespace AmqpClient;
using json = nlohmann::json;

void runWorker(std::string host, int port, std::string user, std::string password, std::shared_ptr<ThreadSafeQueue<ThreadTask>> threadQueue)
{
    fmt::println("Hello from rabbit client");

    Channel::ptr_t channel = Channel::Create(host, port, user, password);
    // char szmsg[1024];

    auto consumerTag = channel->BasicConsume(
        "test",
        "CPP_WORKER",
        true,
        false, // Это автоподтверждение получения
        false,
        1);

    while (true)
    {
        auto envelope = channel->BasicConsumeMessage(consumerTag);
        auto message = envelope->Message();

        fmt::println("Message body is");
        fmt::print("{}\n", message->Body());
        fmt::println("from worker thread");

        auto body = json::parse(message->Body());

        auto promise = std::promise<std::string>(); // Тут будет json с результатом
        auto future = promise.get_future();

        threadQueue->push(ThreadTask{
            // Колбек функция для работы основной программы в дальнейшем.
            // Параметры пробрасываются именно тут
            []()
            {
                return "test test";
            },
            std::move(promise)});

        fmt::print("function result is {}\n", future.get());
        channel->BasicAck(envelope);
    }
}