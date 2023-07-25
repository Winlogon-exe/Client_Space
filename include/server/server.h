#pragma once
#include"boost/asio.hpp"
#include<iostream>
class Connection :public std::enable_shared_from_this<Connection>
{
private:
    boost::asio::ip::tcp::socket socket_;
    std::shared_ptr<boost::asio::streambuf> buffer_;
    void ReadData();
public:
    Connection(boost::asio::io_context& io_context);
    boost::asio::ip::tcp::socket& socket();
    void Start();
};

class Server
{
private:
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    uint16_t port_;
public:
    Server(boost::asio::io_context& io_context, uint16_t port, boost::asio::streambuf& buffer);
    void Listening();

};
