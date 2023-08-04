#pragma once
#include<boost/asio.hpp>
#include<iostream>
class Client
{
private:
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf& buffer_;
    uint16_t port_;
public:
    Client(boost::asio::io_context& io_context, uint16_t port, boost::asio::streambuf& buffer);
    void connectToServer(const std::string& email, const std::string& username, const std::string& password);
    void sendPostRequest(const std::string& data);
    void receiveResponse();
};
