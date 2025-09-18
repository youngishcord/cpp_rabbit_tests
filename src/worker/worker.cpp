#include <memory>
#include <string>

#include <fmt/base.h>
#include <fmt/format.h>

#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <nlohmann/json.hpp>

#include <thread_queue.h>
#include <thread_task.h>

#include "message/result.h"

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

        json result = {
            {"pi", 3.141},
            {"happy", true},
            {"name", "Niels"},
            {"nothing", nullptr},
            {"answer", {{"everything", 42}}},
            {"list", {1, 0, 2}},
            {"object", {{"currency", "USD"}, {"value", 42.99}}}};

        TaskResult taskResult = TaskResult(
            TaskResult::Status::SUCCESS,
            message->CorrelationId(),
            result);

        auto resultString = taskResult.dump();
        // fmt::println(resultString);

        AmqpClient::BasicMessage::ptr_t resultMessage = AmqpClient::BasicMessage::Create();
        resultMessage->ContentType("application/json");
        resultMessage->CorrelationId(message->CorrelationId());
        resultMessage->Body(resultString);

        fmt::print("task id {}\n", message->CorrelationId());
        fmt::print("reply to {}\n", message->ReplyTo());

        channel->BasicPublish("", message->ReplyTo(), resultMessage);

        channel->BasicAck(envelope);
    }
}
