/*
Структура задачи, передаваемая между тредами и синхронизирующая их действия.
*/

#pragma once

#include <future>
#include <thread>

// Структура для хранения задачи и ее результата
struct ThreadTask
{
    // Тут указывается тип данных, который должен быть возвращен, следовательно тут стоит указать какую нибудь структуру
    std::function<std::string()> function;
    std::promise<std::string> promise;
};