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
    void ConnectToServer();
    void SendPostRequest();
    void ReceiveResponse();
};
