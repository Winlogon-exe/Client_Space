#include <QMessageBox>
#include <QDebug>
#include <iostream>

#include "client/client.h"

Client::Client(net::io_context &io_context, uint16_t port) : io_context_(io_context), socket_(io_context), port_(port) {}

void Client::connectToServer(const std::string &email, const std::string &username, const std::string &password)
{
    try {
        net::ip::tcp::resolver resolver(io_context_);
        auto endpoints = resolver.resolve(server_ip, std::to_string(port_));
        net::connect(socket_, endpoints);

        std::string data = "email=" + email + "&username=" + username + "&password=" + password;
        sendPostRequest(data);
    } catch (const std::exception &e) {
       // handleException(e);
    }
}

void Client::sendPostRequest(const std::string &data)
{
    try {
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
    } catch (const std::exception &e) {
        //handleException(e);
    }
}

void Client::receiveResponse(beast::flat_buffer &buffer)
{
    try {
        http::response<http::string_body> res;
        http::read(socket_, buffer, res);

        if (res.result() == http::status::ok)
        {
            qDebug() << "Server response: " << res.body();
        }
        else
        {
            qDebug() << "Failed to connect to server: " << res.result_int();
            //handleServerError(res.result_int());
        }
    } catch (const std::exception &e) {
       // handleException(e);
    }
}

void Client::handleException(const std::exception &e)
{
    qDebug() << "An error occurred: " << e.what();
    QMessageBox::critical(nullptr, "Error", QString::fromStdString("An error occurred: " + std::string(e.what())));
}

void Client::handleServerError(int statusCode)
{
    QString errorMessage = "Failed to connect to server. Status code: " + QString::number(statusCode);
    qDebug() << errorMessage;
    QMessageBox::critical(nullptr, "Connection Error", errorMessage);
}

void Client::sendMessage(const std::string &data)
{
    sendPostRequest(data);
}
