/*
Форматирование сообщений о результате работы работы функции
*/

#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class TaskResult
{
public:
    enum class Status
    {
        SUCCESS,
        FAILURE,
        RETRY,
        PENDING
    };

    TaskResult(Status status, const std::string task_id, json result = nullptr, std::string traceback = "")
        : status_(status), result_(result), taskId_(task_id), traceback_(traceback)
    {
        fmt::print("task id in task resilt constructor is {}\n", task_id);
        // fmt::print("task id is {}\n", task_id);
    }

    // Формирует результат в json
    json to_json() const
    {
        return {
            {"status", status_to_string(status_)},
            {"result", result_},
            {"traceback", ""},
            {"task_id", taskId_}};
    }

    // Сериализует результат в строку
    std::string dump() const
    {
        return to_json().dump();
    }

private:
    Status status_;
    json result_;
    std::string traceback_;
    std::string taskId_;

    static std::string
    status_to_string(Status status)
    {
        switch (status)
        {
        case Status::SUCCESS:
            return "SUCCESS";
        case Status::FAILURE:
            return "FAILURE";
        case Status::RETRY:
            return "RETRY";
        case Status::PENDING:
            return "PENDING";
        }
        return "UNKNOWN";
    }
};
