#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <string>
#include <boost/asio/streambuf.hpp>
#include <QMessageBox>
#include <QDebug>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

class Client
{
private:
    const std::string server_ip = "213.222.226.234";
    net::io_context &io_context_;
    net::ip::tcp::socket socket_;
    uint16_t port_;

public:
    Client(net::io_context &io_context, uint16_t port);

    void connectToServer(const std::string &email, const std::string &username, const std::string &password);
    void sendPostRequest(const std::string &data);
    void receiveResponse(beast::flat_buffer &buffer);
    void sendMessage(const std::string& message);

private:
    void handleException(const std::exception &e);
    void handleServerError(int statusCode);
};
