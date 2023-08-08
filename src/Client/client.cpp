#include<QMessageBox>
#include<QDebug>
#include<iostream>

#include "client/client.h"

Client::Client(net::io_context &io_context, uint16_t port) : io_context_(io_context), socket_(io_context), port_(port) {}

void Client::connectToServer(const std::string &email, const std::string &username, const std::string &password)
{
    net::ip::tcp::resolver resolver(io_context_);
    auto endpoints = resolver.resolve(server_ip, std::to_string(port_));
    net::connect(socket_, endpoints);

    std::string data = "email=" + email + "&username=" + username + "&password=" + password;
    sendPostRequest(data);
}

void Client::sendPostRequest(const std::string &data)
{
    http::request<http::string_body> req;
    req.method(http::verb::post);
    req.target("/post");
    req.version(11);

    req.set(http::field::host, server_ip);
    req.set(http::field::content_type, "text/plain");
    req.set(http::field::content_length, std::to_string(data.size()));

    req.body() = data;

    http::write(socket_, req);

    beast::flat_buffer buffer;
    receiveResponse(buffer);
}

void Client::receiveResponse(beast::flat_buffer &buffer)
{
    http::response<http::string_body> res;
    http::read(socket_, buffer, res);

    if (res.result() == http::status::ok)
    {
        qDebug() << "Server response: " << res.body();
    }
    else
    {
        qDebug() << "Failed to connect to server: " << res.result_int();
        // Выводим сообщение об ошибке пользователю
        QMessageBox::critical(nullptr, "Connection Error", QString::fromStdString("Failed to connect to server: " + std::to_string(res.result_int())));
    }
}
