#pragma once
#include "QString"
#include"boost/asio.hpp"
#include"client.h"

class RunClient {
public:
    static RunClient& getInstance();
    void run(const QString &email, const QString &username, const QString &password);
    void startMessage(const std::string &data); // Добавляем новый метод

    boost::asio::io_context io_context;
    boost::asio::streambuf buffer;
    std::shared_ptr<Client> client;

private:
    RunClient();
    RunClient(const RunClient&) = delete;
    RunClient& operator=(const RunClient&) = delete;
};
