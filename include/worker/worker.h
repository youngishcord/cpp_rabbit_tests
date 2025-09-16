/*
Воркер для работы с очередью rabbitmq
*/

#pragma once

#include <string>

void runWorker(std::string host, int port, std::string user, std::string pass, std::shared_ptr<ThreadSafeQueue<ThreadTask>> threadQueue);
